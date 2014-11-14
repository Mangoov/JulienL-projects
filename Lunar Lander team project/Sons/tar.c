///////////////////////////////////////////////////////////////////////////
/// @file TAR.h
/// @description Implémentation des fontions pour le décodage d'une archive TAR.
/// @version 1.1
///	@date 2013-12
/// @description Implémentation du décodage TAR/Wave.
///	@version 1.1
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

/* Includes */
#include "tar.h"

/* Defines */
#define FLASH_MEM_BASEADDR XPAR_FLASH_MEM0_BASEADDR // adresse absolue choisie pour la page vidéo en RAM DDR2

///////////////////////////////////////////////////////////////////////////
WAV_FILE_TYPE ToEnum(const char* pname)
{
	if(strcmp(pname,"crash.wav") == 0)
	{
		return CRASH;
	}
	else if(strcmp(pname,"fail.wav") == 0)
	{
		return FAIL;
	}
	else if(strcmp(pname,"hurryup.wav") == 0)
	{
		return HURRYUP;
	}
	else if(strcmp(pname,"jet.wav") == 0)
	{
		return JET;
	}
	else if(strcmp(pname,"land.wav") == 0)
	{
		return LAND;
	}
	else if(strcmp(pname,"menuerror.wav") == 0)
	{
		return MENUERROR;
	}
	else if(strcmp(pname,"menuin.wav") == 0)
	{
		return MENUIN;
	}
	else if(strcmp(pname,"menuout.wav") == 0)
	{
		return MENUOUT;
	}
	else if(strcmp(pname,"menuselect.wav") == 0)
	{
		return MENUSELECT;
	}
	else if(strcmp(pname,"pause.wav") == 0)
	{
		return PAUSE;
	}
	else if(strcmp(pname,"start.wav") == 0)
	{
		return START;
	}
	else if(strcmp(pname,"win.wav") == 0)
	{
		return WIN;
	}

	return NO_SOUND;
}


///////////////////////////////////////////////////////////////////////////
uint64_t decodeTarOctal(char* data, size_t size)
{
	unsigned char* currentPtr = (unsigned char*) data + size;
    uint64_t sum = 0;
    uint64_t currentMultiplier = 1;
    unsigned char* checkPtr = currentPtr;
    for (; checkPtr >= (unsigned char*) data; checkPtr--) {
        if ((*checkPtr) == 0 || (*checkPtr) == ' ') {
            currentPtr = checkPtr - 1;
        }
    }
    for (; currentPtr >= (unsigned char*) data; currentPtr--) {
        sum += ASCII_TO_NUMBER(*currentPtr) * currentMultiplier;
        currentMultiplier *= 8;
    }
    return sum;
}


///////////////////////////////////////////////////////////////////////////
size_t getFileSize(TARFileHeader *currentFileHeader)
{
	return decodeTarOctal(currentFileHeader->fileSize, sizeof(currentFileHeader->fileSize));
}


///////////////////////////////////////////////////////////////////////////
bool IsEndOfTarFile(TARFileHeader *currentFileHeader)
{
	char dbgprint[64];

	// Initialize a zero-filled block we can compare against (zero-filled header block --> end of TAR archive)
	char zeroBlock[512];
	memset(zeroBlock, 0, 512);

	// When a block with zeroes-only is found, the TAR archive ends here
	if(memcmp(currentFileHeader, zeroBlock, 512) == 0)
	{
		snprintf(dbgprint, 64, "Found TAR end\n");
		stdout_write_char_array(dbgprint, strlen(dbgprint));
		return true;
	}
	else
		return false;
}


///////////////////////////////////////////////////////////////////////////
void DecodeTar()
{
	char dbgprint[64];
	WAV_FILE_TYPE index = CRASH;
	uint32_t offset = 0;
	size_t paddingBytes;
	TARFileHeader currentFileHeader;

	snprintf(dbgprint, 64, "Start Reading TAR archive...\n");
	stdout_write_char_array(dbgprint, strlen(dbgprint));

	memcpy(&currentFileHeader, (void*)(XPAR_FLASH_MEM0_BASEADDR + offset), sizeof(currentFileHeader));

	while(!IsEndOfTarFile(&currentFileHeader))
	{
		offset += sizeof(currentFileHeader);

		index = ToEnum(currentFileHeader.filename);
		archive.WaveFiles[index].FileSize = getFileSize(&currentFileHeader);
		memcpy(&archive.TARFileHeaders[index], &currentFileHeader, sizeof(currentFileHeader));
		archive.WaveFiles[index].Data = (uint8_t*) malloc(archive.WaveFiles[index].FileSize + 1);

		// Log that we found a file
		snprintf(dbgprint, 64, "Found file '%s'(%u)\n", currentFileHeader.filename, archive.WaveFiles[index].FileSize);
		stdout_write_char_array(dbgprint, strlen(dbgprint));

		// Read the file into memory
		memcpy(archive.WaveFiles[index].Data, (void*)(XPAR_FLASH_MEM0_BASEADDR + offset), archive.WaveFiles[index].FileSize);

		offset += archive.WaveFiles[index].FileSize;

		// In the tar archive, entire 512-byte-blocks are used for each file
		// Therefore we now have to skip the padded bytes.
		paddingBytes = (512 - (archive.WaveFiles[index].FileSize % 512)) % 512; //How long the padding to 512 bytes needs to be
		offset += paddingBytes; // Simply ignore the padding

		memcpy(&currentFileHeader, (void*)(XPAR_FLASH_MEM0_BASEADDR + offset), sizeof(currentFileHeader));
	}
}


///////////////////////////////////////////////////////////////////////////
void DecodeWave()
{
	WAV_FILE_TYPE index = CRASH;
	for(index = CRASH; index < NO_SOUND; ++index)
	{
		memcpy(&archive.WaveFileHeader[index], archive.WaveFiles[index].Data, sizeof(wav_hdr));

		fix_endian_func(&archive.WaveFileHeader[index].ChunkSize, sizeof(uint32_t));

		fix_endian_func(&archive.WaveFileHeader[index].Subchunk1Size, sizeof(uint32_t));
		fix_endian_func(&archive.WaveFileHeader[index].AudioFormat, sizeof(uint16_t));
		fix_endian_func(&archive.WaveFileHeader[index].NumOfChan, sizeof(uint16_t));
		fix_endian_func(&archive.WaveFileHeader[index].SamplesPerSec, sizeof(uint32_t));
		fix_endian_func(&archive.WaveFileHeader[index].bytesPerSec, sizeof(uint32_t));
		fix_endian_func(&archive.WaveFileHeader[index].blockAlign, sizeof(uint16_t));
		fix_endian_func(&archive.WaveFileHeader[index].bitsPerSample, sizeof(uint16_t));
		fix_endian_func(&archive.WaveFileHeader[index].Subchunk2Size, sizeof(uint32_t));

		archive.WaveFiles[index].SampleSize = archive.WaveFileHeader[index].Subchunk2Size;
		archive.WaveFiles[index].RawSample = archive.WaveFiles[index].Data + sizeof(wav_hdr);
		archive.WaveFiles[index].Sample = (uint32_t*) malloc((archive.WaveFiles[index].SampleSize) * sizeof(uint32_t));
	}
}


///////////////////////////////////////////////////////////////////////////
void ProcessSound()
{
	int8_t i8Sample;
	int16_t i16Sample;
	uint32_t ui32Sample;
	WAV_FILE_TYPE index = CRASH;
	size_t j = 0;
	for(index = CRASH; index < NO_SOUND; index++)
	{
		for(j = 0; j < archive.WaveFiles[index].SampleSize; ++j)
		{
			i8Sample = archive.WaveFiles[index].RawSample[j] - 128;
			i16Sample = i8Sample * 255;
			ui32Sample = (uint32_t) i16Sample << 16 | (uint32_t) i16Sample;
			archive.WaveFiles[index].Sample[j] = ui32Sample;
		}
	}
}


///////////////////////////////////////////////////////////////////////////
void PlaySound(ac97_core *CfgAC97, WAV_FILE_TYPE soundType)
{
	size_t i = 0;
	for(i = 0; i < archive.WaveFiles[soundType].SampleSize; ++i)
	 {
		 AC97_playSample(CfgAC97, archive.WaveFiles[soundType].Sample[i]);
	 }
}


///////////////////////////////////////////////////////////////////////////
void InitCurrentSound(WAV_FILE_TYPE SoundType)
{
	if(sound.CurrentState == IDLE || SoundType == WIN) {
		sound.Sample = archive.WaveFiles[SoundType].Sample;
		sound.FileSize = archive.WaveFiles[SoundType].SampleSize;
		sound.CurrentIndex = 0;
		sound.CurrentState = PLAYING;
		sound.SoundType = SoundType;
	}
}

tarFichierHeader fichierHeader;

tarFichierTaille fichierTaille;

waveSampleRate SampleRate;

waveSubchunk2Size Subchunk2Size;

waveData data;

tarFichierHeader gettarFichierHeader(u32 address)
{
  int i;

  for(i=0; i< 100; i++ )
  {
    fichierHeader.echantillon_tar[i] = XIo_In8(address + i);
  }
  return fichierHeader;
}

tarFichierTaille gettarFichierTaille(u32 address)
{
    int i;

	for(i=0; i< 12; i++)
	{

	  fichierTaille.taille_tar[i] = XIo_In8(address + i);

	}
	return fichierTaille;
}

waveSampleRate getwaveSampleRate(u32 address)
{
	int i;

	for(i=0; i< 4; i++ )
	{
		SampleRate.sampleRate_wave[i] = XIo_In8(address + i);
	}

	return SampleRate;
}

waveSubchunk2Size getwaveSubchunk2Size(u32 address)
{
	int i;

	for(i=0; i< 4; i++ )
	{
		Subchunk2Size.subchunk2Size_wave[i] = XIo_In8(address + i);
	}

	return Subchunk2Size;
}


waveData getwaveData(u32 address, u32 taille)
{
	int i;

	for(i=0; i< taille; i++ )
	{
		data.data_wave[i] = XIo_In8(address + i);
	}

	return data;

}

//Reference: http://stackoverflow.com/questions/2505042/how-to-parse-a-tar-file-in-c
//Cette fonction permet de convertir d'octal vers decimal
int octal_string_to_int(char *current_char, unsigned int size)
{
    unsigned int output = 0;
    while(size > 0){
        output = output * 8 + *current_char - '0';
        current_char++;
        size--;
    }
    return output;
}

void decrompresserFileTar(Xuint32 baseAddress)
{
	char dbgprint[64] = { '\0' };
    int i,j,k,r,s,b;
	char nomFile[100];
	int size_of_file;
	char buffer[124];
	u8 sample[4];
	u8 Subchunk[4];
	char strName[100];

	memcpy(&strName[0], (void *)baseAddress, 100);

	//u8 subdata[300000];

	wavesampleTmp sampleTmp;
	waveSubchunTmp SubchunTmp;

	Xuint32 subSize;

	for (s=0; s<12; s++)
	{
		tarFichierHeader fichierHeader;

		fichierHeader = gettarFichierHeader(baseAddress);
		for(i=0; i<100; i++)
		{
			nomFile[i] = fichierHeader.echantillon_tar[i];
		}
		//xil_printf("%s\n", nomFile);


		tarFichierTaille fichierTaille;

		fichierTaille = gettarFichierTaille(baseAddress + 124);
		for(j=0; j<12; j++)
		{
			buffer[j] = fichierTaille.taille_tar[j]; //buffer garde les 12 octal qui corresponde la taille du fichier
			//xil_printf("%x\n", buffer[j]);
		}

		size_of_file = octal_string_to_int(buffer, 11);
		xil_printf("%d\n",  size_of_file);


		waveSampleRate SampleRate;
		SampleRate = getwaveSampleRate(baseAddress + TAR_HEADER + 24);
		for(k=0; k<4; k++)
		{
			sample[k] = SampleRate.sampleRate_wave[k];
			//xil_printf("%x\n", sample);
		}

		//Converstion de little endian vers big endian
		sampleTmp.sampleTmp_wave[0] = sample[3];
		sampleTmp.sampleTmp_wave[1] = sample[2];
		sampleTmp.sampleTmp_wave[2] = sample[1];
		sampleTmp.sampleTmp_wave[3] = sample[0];

		//snprintf(dbgprint, 64, "sampleTmp.sampleTmp_wave[0]:= %d\n", sampleTmp.sampleTmp_wave[0]);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		//snprintf(dbgprint, 64, "sampleTmp.sampleTmp_wave[1]:= %d\n", sampleTmp.sampleTmp_wave[1]);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		//snprintf(dbgprint, 64, "sampleTmp.sampleTmp_wave[2]:= %d\n", sampleTmp.sampleTmp_wave[2]);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		//snprintf(dbgprint, 64, "sampleTmp.sampleTmp_wave[3]:= %d\n", sampleTmp.sampleTmp_wave[3]);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		waveSubchunk2Size Subchunk2Size;
		Subchunk2Size = getwaveSubchunk2Size(baseAddress + TAR_HEADER + 40);
		for(r=0; r<4; r++)
		{
			Subchunk[r] = Subchunk2Size.subchunk2Size_wave[r];
			//xil_printf("%x\n", Subchunk);
		}

		//Converstion de little endian vers big endian
		SubchunTmp.subchunTmp_wave[0] = Subchunk[3];
		SubchunTmp.subchunTmp_wave[1] = Subchunk[2];
		SubchunTmp.subchunTmp_wave[2] = Subchunk[1];
		SubchunTmp.subchunTmp_wave[3] = Subchunk[0];


		//snprintf(dbgprint, 64, "SubchunTmp.subchunTmp_wave[0]:= %d\n", SubchunTmp.subchunTmp_wave[0]);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		//snprintf(dbgprint, 64, "SubchunTmp.subchunTmp_wave[1]:= %d\n", SubchunTmp.subchunTmp_wave[1]);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		//snprintf(dbgprint, 64, "SubchunTmp.subchunTmp_wave[2]:= %d\n", SubchunTmp.subchunTmp_wave[2]);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		//snprintf(dbgprint, 64, "SubchunTmp.subchunTmp_wave[3]:= %d\n", SubchunTmp.subchunTmp_wave[3]);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		memcpy(&subSize, &SubchunTmp.subchunTmp_wave[0], sizeof(Xuint32));

		//snprintf(dbgprint, 64, "subSize:= %d\n", subSize);
		//stdout_write_char_array(dbgprint, strlen(dbgprint));

		waveData data;
		data = getwaveData(baseAddress + TAR_HEADER + 40 + 4, subSize);

		/*for(b=0; b<subSize; b++)
		{

			if(strcmp(nomFile,"crash.wav") == 0)
			{
			  crash[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"fail.wav")==0)
			{
			  fail[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"hurryup.wav")==0)
			{
			  hurryup[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"jet.wav")==0)
			{
			  jet[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"land.wav")==0)
			{
				land[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"menuerror.wav")==0)
			{
			  menuerror[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"menuin.wav")==0)
			{
			  menuin[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"menuout.wav")==0)
			{
			  menuout[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"menuselect.wav")==0)
			{
			  menuselect[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"pause.wav")==0)
			{
			  pauseA[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"start.wav")==0)
			{
			  startA[b] = data.data_wave[b];
			}

			if(strcmp(nomFile,"win.wav")==0)
			{
			  win[b] = data.data_wave[b];
			}
		}*/

        //baseAddres, ici on calcule l'entete du fichier suivant
		baseAddress += TAR_HEADER + ((size_of_file / TAR_HEADER) + 1) * TAR_HEADER;
	}

}

void LoadSound()
{
	DecodeTar();
	DecodeWave();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////



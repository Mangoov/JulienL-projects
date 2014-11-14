///////////////////////////////////////////////////////////////////////////
/// @file UtilitaireINF2990.h
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ENVIRONNEMENT_UTILITAIREINF2990_H__
#define __ENVIRONNEMENT_UTILITAIREINF2990_H__


#include <jni.h>
#include <string>


namespace utilitaire {


   /// Effectue une conversion entre une cha�ne Java et une cha�ne C++.
   std::string obtenirChaineISO(JNIEnv* env, jstring chaine);


}


#endif // __ENVIRONNEMENT_UTILITAIREINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

/*
    OS dependent macros

Copyright 2010-2011 Sampo Savolainen (v2@iki.fi). All rights reserved.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, 
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

   3. Neither the name of Foo YC20 nor the names of its contributors may be 
      used to endorse or promote products derived from this software without
      specific prior written permission.

THIS SOFTWARE IS PROVIDED BY SAMPO SAVOLAINEN ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL SAMPO SAVOLAINEN OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OFSUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHERIN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISEDOF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _YC20_OS_H
#define _YC20_OS_H


#define SHARE_DIR "/share/foo-yc20/"
#define YC20_PNG_DIR "graphics/"


#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)

#define PREFIX_STR STR(PREFIX)
#define VERSION_STR STR(VERSION)



#ifdef __APPLE__
//#warning "Selected OS X directories"

#define DEFAULT_CONFIG_DIR std::string(getenv("HOME")) + "/Library/Application Support/foo-yc20/"

#ifdef OSXLV2 // OSX LV2
#define INSTALL_LOCATION PREFIX_STR SHARE_DIR
#elif defined OSXVST
const char * get_bundle_path(void);
#define INSTALL_LOCATION std::string(get_bundle_path()) + "/" +
#else // OSX app bundle
#define INSTALL_LOCATION "../Resources/"
#endif
#endif

#ifdef __WIN32__
//#warning "Selected WIN32 directories"

#define DEFAULT_CONFIG_DIR \
  std::string( \
    getenv("HOMEPATH")?getenv("HOMEPATH"): \
      (getenv("HOME")?getenv("HOME"):"") \
  ) + "\\foo-yc20"

// this is wrong, but we will live
#define INSTALL_LOCATION PREFIX_STR SHARE_DIR
#endif


#ifndef DEFAULT_CONFIG_DIR
//#warning "Selected Linux/UNIX directories"

#define DEFAULT_CONFIG_DIR std::string(getenv("HOME")) + "/.foo-yc20"
#define INSTALL_LOCATION PREFIX_STR SHARE_DIR
#endif


#endif /* _YC20_OS_H */


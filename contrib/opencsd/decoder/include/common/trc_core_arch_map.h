/*!
 * \file       trc_core_arch_map.h
 * \brief      OpenCSD : Map core name strings to architecture profile constants.
 * 
 * \copyright  Copyright (c) 2015, ARM Limited. All Rights Reserved.
 */

/* 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution. 
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors 
 * may be used to endorse or promote products derived from this software without 
 * specific prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */ 

#ifndef ARM_TRC_CORE_ARCH_MAP_H_INCLUDED
#define ARM_TRC_CORE_ARCH_MAP_H_INCLUDED

#include <map>
#include <string>
#include "opencsd/ocsd_if_types.h"

class CoreArchProfileMap
{
public:
    CoreArchProfileMap();
    ~CoreArchProfileMap() {};

    ocsd_arch_profile_t getArchProfile(const std::string &coreName);

private:

    std::map<std::string, ocsd_arch_profile_t> core_profiles;
};

inline ocsd_arch_profile_t CoreArchProfileMap::getArchProfile(const std::string &coreName)
{
    ocsd_arch_profile_t ap = { ARCH_UNKNOWN, profile_Unknown };

    std::map<std::string, ocsd_arch_profile_t>::const_iterator it;
    it = core_profiles.find(coreName);
    if(it != core_profiles.end())
        ap = it->second;
    return ap;
}

#endif // ARM_TRC_CORE_ARCH_MAP_H_INCLUDED

/* End of File trc_core_arch_map.h */

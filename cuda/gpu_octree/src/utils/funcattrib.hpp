/*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2011, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
*  Author: Anatoly Baskeheev, Itseez Ltd, (myname.mysurname@mycompany.com)
*/

#ifndef PCL_GPU_OCTREE_UTILS_HPP_
#define PCL_GPU_OCTREE_UTILS_HPP_

#include<cstdio>

namespace pcl
{
    namespace cuda
    {
        template<class Func> 
        void printFuncAttrib(Func& func)
        {

            cudaFuncAttributes attrs;
            cudaFuncGetAttributes(&attrs, func);  

            printf("=== Function stats ===\n");
            printf("Name: \n");
            printf("sharedSizeBytes    = %d\n", attrs.sharedSizeBytes);
            printf("constSizeBytes     = %d\n", attrs.constSizeBytes);
            printf("localSizeBytes     = %d\n", attrs.localSizeBytes);
            printf("maxThreadsPerBlock = %d\n", attrs.maxThreadsPerBlock);
            printf("numRegs            = %d\n", attrs.numRegs);
            printf("ptxVersion         = %d\n", attrs.ptxVersion);
            printf("binaryVersion      = %d\n", attrs.binaryVersion);
            printf("\n");
            fflush(stdout); 
        }
    }

}

#endif  /* PCL_GPU_OCTREE_UTILS_HPP_ */
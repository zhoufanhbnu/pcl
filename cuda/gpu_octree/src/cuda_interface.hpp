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

#ifndef PCL_GPU_CUDA_OCTREE_
#define PCL_GPU_CUDA_OCTREE_

#include "pcl/gpu/common/device_array.hpp"
#include "pcl/gpu/octree/octree.hpp"

#include "octree_global.hpp"
#include "tasks_global.hpp"

namespace pcl
{
    namespace gpu
    {          
        class OctreeImpl
        {
        public:
            typedef Octree::BatchQueries BatchQueries;
            typedef Octree::BatchResult BatchResult;
            typedef Octree::BatchResultSizes BatchResultSizes;

            static void get_gpu_arch_compiled_for(int& bin, int& ptr);


            OctreeImpl(int number_of_SMs_arg) : number_of_SMs(number_of_SMs_arg) {};
            ~OctreeImpl() {};

            void setCloud(const DeviceArray_<float3>& input_points);           
            void build();
            void radiusSearchHost(const float3& center, float radius, std::vector<int>& out, int max_nn) const;
            
            void radiusSearchBatch(const DeviceArray_<float3>& queries, float radius, int max_results, BatchResult& output, BatchResultSizes& out_sizes);

            size_t points_num;

                        
            DeviceArray_<float3> points;
            DeviceArray_<float3> points_sorted;

            DeviceArray_<int> codes;
            DeviceArray_<int> indices;
                        
            pcl::device::TasksGlobal tasksGlobal;
            pcl::device::OctreeGlobalWithBox octreeGlobal;    

            //storage
            DeviceArray2D_<int> storage;            

            struct OctreeDataHost
            {
                std::vector<int> nodes;

                std::vector<int> begs;
                std::vector<int> ends;	
                std::vector<int> node_codes;	

                std::vector<int> indices;	
                
                std::vector<float3> points_sorted;

                int downloaded;

            } host_octree;

                        
            void internalDownload();

            int number_of_SMs;
        };
    }
}

#endif /* PCL_GPU_CUDA_OCTREE_ */

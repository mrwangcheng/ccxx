
# Utility function: adds sample executable target with name "example_<group>_<file_name>"
# Usage:
#   ocv_define_sample(<output target> <relative filename> <group>)
function(ocv_define_sample out_target source sub)
    get_filename_component(name "${source}" NAME_WE)
    if(name MATCHES "main")
        message("-------------------------- 1 " ${source})
        message("-------------------------- 1 " ${name})
    else()
        set(the_target "opencv_${sub}_${name}")
        add_executable(${the_target} "${source}")
        set_target_properties(${the_target} PROPERTIES PROJECT_LABEL "(cxtext_opencv) ${name}")
        if(ENABLE_SOLUTION_FOLDERS)
            set_target_properties(${the_target} PROPERTIES FOLDER "cxtext_opencv/${sub}")
        endif()
        if(WIN32 AND MSVC AND NOT BUILD_SHARED_LIBS)
            set_target_properties(${the_target} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:atlthunk.lib /NODEFAULTLIB:atlsd.lib /DEBUG")
        endif()
        if(WIN32)
            install(TARGETS ${the_target} RUNTIME DESTINATION "cxtext_opencv/${sub}" COMPONENT cxtext_opencv)
        endif()
        # Add single target to build all samples in the group: 'make opencv_samples_cpp'
        set(parent_target opencv_samples_${sub})
        if(NOT TARGET ${parent_target})
            add_custom_target(${parent_target})
            if(TARGET opencv_samples)
                add_dependencies(cxtest_opencvs ${parent_target})
            endif()
        endif()
        add_dependencies(${parent_target} ${the_target})
        set(${out_target} ${the_target} PARENT_SCOPE)
    endif()
endfunction()


#message("----------------- xxx ------ : " ${gsl_opencv_sample_sources})

mc_list_filterout(gsl_opencv_sample_sources "/gpu/")
mc_list_filterout(gsl_opencv_sample_sources "real_time_pose_estimation/")
foreach(sample_filename ${gsl_opencv_sample_sources})
    set(package "cpp")
    if(sample_filename MATCHES "tutorial_code")
        set(package "tutorial")
    endif()
    ocv_define_sample(tgt ${sample_filename} ${package})
    mc_target_link_opencv(${tgt})
    # ocv_target_link_libraries(${tgt} ${OPENCV_LINKER_LIBS} ${OPENCV_CPP_SAMPLES_REQUIRED_DEPS})
    if(sample_filename MATCHES "/viz/")
        # ocv_target_link_libraries(${tgt} ${VTK_LIBRARIES})
        target_compile_definitions(${tgt} PRIVATE -DUSE_VTK)
    endif()
    if(HAVE_OPENGL AND sample_filename MATCHES "detect_mser")
        target_compile_definitions(${tgt} PRIVATE HAVE_OPENGL)
    endif()
endforeach()

#include("tutorial_code/calib3d/real_time_pose_estimation/CMakeLists.txt" OPTIONAL)

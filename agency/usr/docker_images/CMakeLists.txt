# This target is used to copy the Docker images .
#
# It manages the different supported architectures ('aarch32' & 'aarch64')

set(DOCKER_IMAGES_COPY_PATH ${CMAKE_BINARY_DIR}/root/docker_images)

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64")
	install(DIRECTORY aarch64/ DESTINATION ${DOCKER_IMAGES_COPY_PATH})
else()
	message( STATUS " JMI - 32it !" )
	#add_subdirectory(aarch32)
endif()

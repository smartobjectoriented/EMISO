.. _portainer:

#########
Portainer
#########

*Portainer CE* (Community Edition) is an open-source container management tool
that simplifies the deployment, management, and monitoring of Docker containers
and containerized applications. It provides a user-friendly web-based interface
that allows users to interact with Docker and manage containers, images, networks,
and volumes without needing to use complex command-line tools.

In the context of the EMISO project, *Portainer* will be employed and customized
to extend its functionality in order to effectively support SO3 Containers.


It is build in tow parts: *Portainer Server* which runs on the Host/control PC
and a *Portainer-Agent* running in each *Smart Object*.

******
Server
******

The *Portainer Server* can be started directly from a docker image.

.. code-block:: shell

	$ docker volume create portainer_data
	$ docker run -d -p 8000:8000 -p 9443:9443 \
       --name portainer \
       --restart=always \
       -v /var/run/docker.sock:/var/run/docker.sock \
       -v portainer_data:/data \
       portainer/portainer-ce:latest


*****
Agent
*****

The Agent is also deployed from a docker image, bellow is the docker run command
to start it.

.. code-block:: shell

	$ docker run -d \
           -p 9001:9001 \
           --name portainer_agent \
           --restart=always \
           -v /var/run/docker.sock:/var/run/docker.sock \
           -v /var/lib/docker/volumes:/var/lib/docker/volumes \
            portainer/agent:2.18.4

During the initial boot of the system, the process consists of extracting the *Portainer-agent*
image, loading it into Docker, and subsequently executing it using the docker run
command.
After this initial setup, the *Portainer-agent* container is configured to be launched
automatically at every system boot.

All this steps are handled by ``S62Portainer`` ``init.d`` script.

The docker image is stored, in the target, at ``/root/docker_images/portainer_agent_image.zip``

.. note::

	The container starts automatically at boot. If it is manually stopped, it is
	restarted only when Docker daemon restarts or the container itself is manually
	restarted.


***********
Basic usage
***********

TBD

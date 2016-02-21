default: | build-gps-speedo flash-gps-speedo
build-gps-speedo:
	cd spark-firmware/main && \
		make PLATFORM=photon APPDIR=$(CURDIR)/src

clean-gps-speedo:
	cd spark-firmware/main && \
		make PLATFORM=photon APPDIR=$(CURDIR)/src clean

flash-gps-speedo:
	cd spark-firmware/main && \
		export PARTICLE_SERIAL_DEV=/dev/ttyACM0 && \
		make PLATFORM=photon APPDIR=$(CURDIR)/src program-dfu


first-time-setup: | build-spark-firmware flash-spark-firmware set-up-wifi
build-spark-firmware:
	cd spark-firmware/modules && \
		make PLATFORM=photon clean all

flash-spark-firmware:
	cd spark-firmware/modules && \
		export PARTICLE_SERIAL_DEV=/dev/ttyACM0 && \
		make PLATFORM=photon program-dfu


# If you don't do this, the DFU loaded application
# firmware will not start. Weird, but true.
set-up-wifi:
	@echo Preess 'w' and set up the WiFi
	screen /dev/ttyACM0

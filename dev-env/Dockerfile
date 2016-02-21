FROM base/archlinux

# Particle software
RUN pacman -Syyu && \
    pacman -S nodejs npm
RUN npm install -g particle-cli

# Flashing over USB
RUN pacman -Syyu && \
    pacman -S dfu-util

# Building locally
RUN pacman -Syyu && \
    pacman -S arm-none-eabi-gcc arm-none-eabi-newlib make

# The "correct" crc32
ADD crc32.c
RUN gcc -lz -o /usr/local/bin/crc32 crc32.c
RUN chmod a+x /usr/local/bin/crc32

# Flash as non-root
RUN cp /usr/lib/node_modules/particle-cli/lib/50-particle.rules /etc/udev/rules.d/50-particle.rules
RUN sed -i.bak s/plugdev/users/g /etc/udev/rules.d/50-particle.rules


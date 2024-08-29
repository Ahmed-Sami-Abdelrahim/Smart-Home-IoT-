# Include the core image recipe as a base.
include recipes-core/images/core-image-minimal.bb

# Add features to the image, such as an SSH server using Dropbear.
IMAGE_FEATURES += "ssh-server-dropbear"

# Install additional packages into the image.
IMAGE_INSTALL += "nginx kernel-modules device-control frontend"
IMAGE_INSTALL:append = " linux-firmware-bcm43430 bluez5 dhcpcd iptables wpa-supplicant"

# Install additional firmware packages.
CORE_IMAGE_EXTRA_INSTALL += "linux-firmware-bcm43455"

# Automatically load the gpiodriver kernel module.
KERNEL_MODULE_AUTOLOAD += "gpiodriver"

# Function to set a fixed IP address for wlan0.
my_fixed_ip() {
    echo "
    interface wlan0
    static ip_address=192.168.1.114/24
    static routers=192.168.1.1
    static domain_name_servers=192.168.1.1 8.8.8.8
    " >> ${IMAGE_ROOTFS}/etc/dhcpcd.conf
}

# Execute the my_fixed_ip function during rootfs post-installation.
ROOTFS_POSTINSTALL_COMMAND += " my_fixed_ip; "

# Kernel informations
BOARD_KERNEL_CMDLINE := androidboot.hardware=qcom user_debug=22 zcache msm_rtb.filter=0x3F ehci-hcd.park=3 androidboot.bootdevice=msm_sdcc.1
BOARD_KERNEL_BASE := 0x80200000
BOARD_MKBOOTIMG_ARGS := --ramdisk_offset 0x02000000
BOARD_KERNEL_PAGESIZE := 2048
TARGET_KERNEL_SOURCE := kernel/samsung/msm8930-common
TARGET_KERNEL_CONFIG := samsung_loganre_defconfig
TARGET_KERNEL_VARIANT_CONFIG := msm8930_loganre_eur_lte_defconfig

# Media codecs
PRODUCT_COPY_FILES += \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:system/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:system/etc/media_codecs_google_telephony.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video_le.xml:system/etc/media_codecs_google_video_le.xml

# OMX packages
PRODUCT_PACKAGES += \
    libc2dcolorconvert \
    libdivxdrmdecrypt \
    libmm-omxcore \
    libOmxCore \
    libOmxVenc \
    libOmxVdec \
    libOmxAacEnc \
    libOmxAmrEnc \
    libOmxEvrcEnc \
    libOmxQcelp13Enc \
    libstagefrighthw

# DRM packages
PRODUCT_PACKAGES += \
    com.google.widevine.software.drm

# DRM properties
PRODUCT_PROPERTY_OVERRIDES += \
    drm.service.enabled=true \
    media.stagefright.legacyencoder=true \
    media.stagefright.less-secure=true \
    qcom.hw.aac.encoder=true

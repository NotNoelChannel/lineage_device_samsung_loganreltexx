/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define LOG_TAG "CameraParams"
#include <utils/Log.h>

#include <string.h>
#include <stdlib.h>
#include <camera/CameraParameters.h>
#include <system/graphics.h>

namespace android {
// Parameter keys to communicate between camera application and driver.
const char CameraParameters::KEY_PREVIEW_SIZE[] = "preview-size";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_SIZES[] = "preview-size-values";
const char CameraParameters::KEY_PREVIEW_FORMAT[] = "preview-format";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FORMATS[] = "preview-format-values";
const char CameraParameters::KEY_PREVIEW_FRAME_RATE[] = "preview-frame-rate";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES[] = "preview-frame-rate-values";
const char CameraParameters::KEY_PREVIEW_FPS_RANGE[] = "preview-fps-range";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FPS_RANGE[] = "preview-fps-range-values";
const char CameraParameters::KEY_PICTURE_SIZE[] = "picture-size";
const char CameraParameters::KEY_SUPPORTED_PICTURE_SIZES[] = "picture-size-values";
const char CameraParameters::KEY_PICTURE_FORMAT[] = "picture-format";
const char CameraParameters::KEY_SUPPORTED_PICTURE_FORMATS[] = "picture-format-values";
const char CameraParameters::KEY_JPEG_THUMBNAIL_WIDTH[] = "jpeg-thumbnail-width";
const char CameraParameters::KEY_JPEG_THUMBNAIL_HEIGHT[] = "jpeg-thumbnail-height";
const char CameraParameters::KEY_SUPPORTED_JPEG_THUMBNAIL_SIZES[] = "jpeg-thumbnail-size-values";
const char CameraParameters::KEY_JPEG_THUMBNAIL_QUALITY[] = "jpeg-thumbnail-quality";
const char CameraParameters::KEY_JPEG_QUALITY[] = "jpeg-quality";
const char CameraParameters::KEY_ROTATION[] = "rotation";
const char CameraParameters::KEY_GPS_LATITUDE[] = "gps-latitude";
const char CameraParameters::KEY_GPS_LONGITUDE[] = "gps-longitude";
const char CameraParameters::KEY_GPS_ALTITUDE[] = "gps-altitude";
const char CameraParameters::KEY_GPS_TIMESTAMP[] = "gps-timestamp";
const char CameraParameters::KEY_GPS_PROCESSING_METHOD[] = "gps-processing-method";
const char CameraParameters::KEY_WHITE_BALANCE[] = "whitebalance";
const char CameraParameters::KEY_SUPPORTED_WHITE_BALANCE[] = "whitebalance-values";
const char CameraParameters::KEY_EFFECT[] = "effect";
const char CameraParameters::KEY_SUPPORTED_EFFECTS[] = "effect-values";
const char CameraParameters::KEY_ANTIBANDING[] = "antibanding";
const char CameraParameters::KEY_SUPPORTED_ANTIBANDING[] = "antibanding-values";
const char CameraParameters::KEY_SCENE_MODE[] = "scene-mode";
const char CameraParameters::KEY_SUPPORTED_SCENE_MODES[] = "scene-mode-values";
const char CameraParameters::KEY_FLASH_MODE[] = "flash-mode";
const char CameraParameters::KEY_SUPPORTED_FLASH_MODES[] = "flash-mode-values";
const char CameraParameters::KEY_FOCUS_MODE[] = "focus-mode";
const char CameraParameters::KEY_SUPPORTED_FOCUS_MODES[] = "focus-mode-values";
const char CameraParameters::KEY_MAX_NUM_FOCUS_AREAS[] = "max-num-focus-areas";
const char CameraParameters::KEY_FOCUS_AREAS[] = "focus-areas";
const char CameraParameters::KEY_FOCAL_LENGTH[] = "focal-length";
const char CameraParameters::KEY_HORIZONTAL_VIEW_ANGLE[] = "horizontal-view-angle";
const char CameraParameters::KEY_VERTICAL_VIEW_ANGLE[] = "vertical-view-angle";
const char CameraParameters::KEY_EXPOSURE_COMPENSATION[] = "exposure-compensation";
const char CameraParameters::KEY_MAX_EXPOSURE_COMPENSATION[] = "max-exposure-compensation";
const char CameraParameters::KEY_MIN_EXPOSURE_COMPENSATION[] = "min-exposure-compensation";
const char CameraParameters::KEY_EXPOSURE_COMPENSATION_STEP[] = "exposure-compensation-step";
const char CameraParameters::KEY_AUTO_EXPOSURE_LOCK[] = "auto-exposure-lock";
const char CameraParameters::KEY_AUTO_EXPOSURE_LOCK_SUPPORTED[] = "auto-exposure-lock-supported";
const char CameraParameters::KEY_AUTO_WHITEBALANCE_LOCK[] = "auto-whitebalance-lock";
const char CameraParameters::KEY_AUTO_WHITEBALANCE_LOCK_SUPPORTED[] = "auto-whitebalance-lock-supported";
const char CameraParameters::KEY_MAX_NUM_METERING_AREAS[] = "max-num-metering-areas";
const char CameraParameters::KEY_METERING_AREAS[] = "metering-areas";
const char CameraParameters::KEY_ZOOM[] = "zoom";
const char CameraParameters::KEY_MAX_ZOOM[] = "max-zoom";
const char CameraParameters::KEY_ZOOM_RATIOS[] = "zoom-ratios";
const char CameraParameters::KEY_ZOOM_SUPPORTED[] = "zoom-supported";
const char CameraParameters::KEY_SMOOTH_ZOOM_SUPPORTED[] = "smooth-zoom-supported";
const char CameraParameters::KEY_FOCUS_DISTANCES[] = "focus-distances";
const char CameraParameters::KEY_VIDEO_FRAME_FORMAT[] = "video-frame-format";
const char CameraParameters::KEY_VIDEO_SIZE[] = "video-size";
const char CameraParameters::KEY_SUPPORTED_VIDEO_SIZES[] = "video-size-values";
const char CameraParameters::KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO[] = "preferred-preview-size-for-video";
const char CameraParameters::KEY_MAX_NUM_DETECTED_FACES_HW[] = "max-num-detected-faces-hw";
const char CameraParameters::KEY_MAX_NUM_DETECTED_FACES_SW[] = "max-num-detected-faces-sw";
const char CameraParameters::KEY_RECORDING_HINT[] = "recording-hint";
const char CameraParameters::KEY_VIDEO_SNAPSHOT_SUPPORTED[] = "video-snapshot-supported";
const char CameraParameters::KEY_VIDEO_STABILIZATION[] = "video-stabilization";
const char CameraParameters::KEY_VIDEO_STABILIZATION_SUPPORTED[] = "video-stabilization-supported";
const char CameraParameters::KEY_LIGHTFX[] = "light-fx";

const char CameraParameters::TRUE[] = "true";
const char CameraParameters::FALSE[] = "false";
const char CameraParameters::FOCUS_DISTANCE_INFINITY[] = "Infinity";

// Values for white balance settings.
const char CameraParameters::WHITE_BALANCE_AUTO[] = "auto";
const char CameraParameters::WHITE_BALANCE_INCANDESCENT[] = "incandescent";
const char CameraParameters::WHITE_BALANCE_FLUORESCENT[] = "fluorescent";
const char CameraParameters::WHITE_BALANCE_WARM_FLUORESCENT[] = "warm-fluorescent";
const char CameraParameters::WHITE_BALANCE_DAYLIGHT[] = "daylight";
const char CameraParameters::WHITE_BALANCE_CLOUDY_DAYLIGHT[] = "cloudy-daylight";
const char CameraParameters::WHITE_BALANCE_TWILIGHT[] = "twilight";
const char CameraParameters::WHITE_BALANCE_SHADE[] = "shade";

// Values for effect settings.
const char CameraParameters::EFFECT_NONE[] = "none";
const char CameraParameters::EFFECT_MONO[] = "mono";
const char CameraParameters::EFFECT_NEGATIVE[] = "negative";
const char CameraParameters::EFFECT_SOLARIZE[] = "solarize";
const char CameraParameters::EFFECT_SEPIA[] = "sepia";
const char CameraParameters::EFFECT_POSTERIZE[] = "posterize";
const char CameraParameters::EFFECT_WHITEBOARD[] = "whiteboard";
const char CameraParameters::EFFECT_BLACKBOARD[] = "blackboard";
const char CameraParameters::EFFECT_AQUA[] = "aqua";

// Values for antibanding settings.
const char CameraParameters::ANTIBANDING_AUTO[] = "auto";
const char CameraParameters::ANTIBANDING_50HZ[] = "50hz";
const char CameraParameters::ANTIBANDING_60HZ[] = "60hz";
const char CameraParameters::ANTIBANDING_OFF[] = "off";

// Values for flash mode settings.
const char CameraParameters::FLASH_MODE_OFF[] = "off";
const char CameraParameters::FLASH_MODE_AUTO[] = "auto";
const char CameraParameters::FLASH_MODE_ON[] = "on";
const char CameraParameters::FLASH_MODE_RED_EYE[] = "red-eye";
const char CameraParameters::FLASH_MODE_TORCH[] = "torch";

// Values for scene mode settings.
const char CameraParameters::SCENE_MODE_AUTO[] = "auto";
const char CameraParameters::SCENE_MODE_ACTION[] = "action";
const char CameraParameters::SCENE_MODE_PORTRAIT[] = "portrait";
const char CameraParameters::SCENE_MODE_LANDSCAPE[] = "landscape";
const char CameraParameters::SCENE_MODE_NIGHT[] = "night";
const char CameraParameters::SCENE_MODE_NIGHT_PORTRAIT[] = "night-portrait";
const char CameraParameters::SCENE_MODE_THEATRE[] = "theatre";
const char CameraParameters::SCENE_MODE_BEACH[] = "beach";
const char CameraParameters::SCENE_MODE_SNOW[] = "snow";
const char CameraParameters::SCENE_MODE_SUNSET[] = "sunset";
const char CameraParameters::SCENE_MODE_STEADYPHOTO[] = "steadyphoto";
const char CameraParameters::SCENE_MODE_FIREWORKS[] = "fireworks";
const char CameraParameters::SCENE_MODE_SPORTS[] = "sports";
const char CameraParameters::SCENE_MODE_PARTY[] = "party";
const char CameraParameters::SCENE_MODE_CANDLELIGHT[] = "candlelight";
const char CameraParameters::SCENE_MODE_BARCODE[] = "barcode";
const char CameraParameters::SCENE_MODE_HDR[] = "hdr";

const char CameraParameters::PIXEL_FORMAT_YUV422SP[] = "yuv422sp";
const char CameraParameters::PIXEL_FORMAT_YUV420SP[] = "yuv420sp";
const char CameraParameters::PIXEL_FORMAT_YUV422I[] = "yuv422i-yuyv";
const char CameraParameters::PIXEL_FORMAT_YUV420P[]  = "yuv420p";
const char CameraParameters::PIXEL_FORMAT_RGB565[] = "rgb565";
const char CameraParameters::PIXEL_FORMAT_RGBA8888[] = "rgba8888";
const char CameraParameters::PIXEL_FORMAT_JPEG[] = "jpeg";
const char CameraParameters::PIXEL_FORMAT_BAYER_RGGB[] = "bayer-rggb";
const char CameraParameters::PIXEL_FORMAT_ANDROID_OPAQUE[] = "android-opaque";

// Values for focus mode settings.
const char CameraParameters::FOCUS_MODE_AUTO[] = "auto";
const char CameraParameters::FOCUS_MODE_INFINITY[] = "infinity";
const char CameraParameters::FOCUS_MODE_MACRO[] = "macro";
const char CameraParameters::FOCUS_MODE_FIXED[] = "fixed";
const char CameraParameters::FOCUS_MODE_EDOF[] = "edof";
const char CameraParameters::FOCUS_MODE_CONTINUOUS_VIDEO[] = "continuous-video";
const char CameraParameters::FOCUS_MODE_CONTINUOUS_PICTURE[] = "continuous-picture";

// Values for light fx settings
const char CameraParameters::LIGHTFX_LOWLIGHT[] = "low-light";
const char CameraParameters::LIGHTFX_HDR[] = "high-dynamic-range";

// Custom parameters for Samsung
const char CameraParameters::KEY_SUPPORTED_ISO_MODES[] = "iso-values";
const char CameraParameters::KEY_QC_FACE_RECOGNITION[] = "face-recognition";
const char CameraParameters::KEY_QC_SUPPORTED_FACE_RECOGNITION[] = "face-recognition-values";
const char CameraParameters::KEY_QC_SUPPORTED_FACE_RECOGNITION_MODES[] = "face-recognition-values";
const char CameraParameters::KEY_QC_FACE_DETECTION[] = "face-detection";
const char CameraParameters::KEY_QC_SUPPORTED_FACE_DETECTION[] = "face-detection-values";
const char CameraParameters::KEY_FACE_DETECTION[] = "face-detection";
const char CameraParameters::KEY_SUPPORTED_FACE_DETECTION[] = "face-detection-values";
const char CameraParameters::FACE_DETECTION_OFF[] = "off";
const char CameraParameters::FACE_DETECTION_ON[] = "on";
const char CameraParameters::KEY_ZSL[] = "zsl";
const char CameraParameters::KEY_SUPPORTED_ZSL_MODES[] = "zsl-values";
const char CameraParameters::ZSL_OFF[] = "off";
const char CameraParameters::ZSL_ON[] = "on";
const char CameraParameters::KEY_ISO_MODE[] = "iso";
const char CameraParameters::KEY_CAMERA_MODE[] = "camera-mode";
const char CameraParameters::KEY_SAMSUNG_CAMERA_MODE[] = "cam_mode";
const char CameraParameters::KEY_SELECTABLE_ZONE_AF[] = "selectable-zone-af";
const char CameraParameters::KEY_SUPPORTED_SELECTABLE_ZONE_AF[] = "selectable-zone-af-values";
const char CameraParameters::SELECTABLE_ZONE_AF_AUTO[] = "auto";
const char CameraParameters::SELECTABLE_ZONE_AF_SPOT_METERING[] = "spot-metering";
const char CameraParameters::SELECTABLE_ZONE_AF_CENTER_WEIGHTED[] = "center-weighted";
const char CameraParameters::SELECTABLE_ZONE_AF_FRAME_AVERAGE[] = "frame-average";
const char CameraParameters::KEY_PREVIEW_FRAME_RATE_MODE[] = "preview-frame-rate-mode";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATE_MODES[] = "preview-frame-rate-modes";
const char CameraParameters::KEY_PREVIEW_FRAME_RATE_AUTO_MODE[] = "frame-rate-auto";
const char CameraParameters::KEY_PREVIEW_FRAME_RATE_FIXED_MODE[] = "frame-rate-fixed";
const char CameraParameters::KEY_SHARPNESS[] = "sharpness";
const char CameraParameters::KEY_SATURATION[] = "saturation";
const char CameraParameters::KEY_CONTRAST[] = "contrast";
const char CameraParameters::KEY_SCENE_DETECT[] = "scene-detect";
const char CameraParameters::KEY_SUPPORTED_SCENE_DETECT[] = "scene-detect-values";
const char CameraParameters::SCENE_DETECT_OFF[] = "off";
const char CameraParameters::SCENE_DETECT_ON[] = "on";
const char CameraParameters::KEY_WEATHER[] = "weather";
const char CameraParameters::KEY_CITYID[] = "contextualtag-cityid";
const char CameraParameters::KEY_TOUCH_AF_AEC[] = "touch-af-aec";
const char CameraParameters::KEY_SUPPORTED_TOUCH_AF_AEC[] = "touch-af-aec-values";
const char CameraParameters::TOUCH_AF_AEC_OFF[] = "touch-off";
const char CameraParameters::TOUCH_AF_AEC_ON[] = "touch-on";
const char CameraParameters::KEY_MEMORY_COLOR_ENHANCEMENT[] = "mce";
const char CameraParameters::KEY_LENSSHADE[] = "lensshade";
const char CameraParameters::KEY_REDEYE_REDUCTION[] = "redeye-reduction";
const char CameraParameters::KEY_SUPPORTED_REDEYE_REDUCTION[] = "redeye-reduction-values";
const char CameraParameters::REDEYE_REDUCTION_ENABLE[] = "enable";
const char CameraParameters::REDEYE_REDUCTION_DISABLE[] = "disable";
const char CameraParameters::KEY_GPS_LATITUDE_REF[] = "gps-latitude-ref";
const char CameraParameters::KEY_GPS_LONGITUDE_REF[] = "gps-longitude-ref";
const char CameraParameters::KEY_GPS_ALTITUDE_REF[] = "gps-altitude-ref";
const char CameraParameters::KEY_GPS_STATUS[] = "gps-status";
const char CameraParameters::KEY_EXIF_DATETIME[] = "exif-datetime";
const char CameraParameters::KEY_AUTO_EXPOSURE[] = "auto-exposure";
const char CameraParameters::KEY_SUPPORTED_AUTO_EXPOSURE[] = "auto-exposure-values";
const char CameraParameters::KEY_SUPPORTED_LENSSHADE_MODES[] = "lensshade-values";
const char CameraParameters::LENSSHADE_ENABLE[] = "enable";
const char CameraParameters::LENSSHADE_DISABLE[] = "disable";
const char CameraParameters::MCE_ENABLE[] = "enable";
const char CameraParameters::MCE_DISABLE[] = "disable";
const char CameraParameters::ISO_AUTO[] = "auto";
const char CameraParameters::ISO_HJR[] = "ISO_HJR";
const char CameraParameters::ISO_100[] = "ISO100";
const char CameraParameters::ISO_200[] = "ISO200";
const char CameraParameters::ISO_400[] = "ISO400";
const char CameraParameters::ISO_800[] = "ISO800";
const char CameraParameters::ISO_1600[] = "ISO1600";
const char CameraParameters::ISO_3200[] = "ISO3200";
const char CameraParameters::ISO_6400[] = "ISO6400";
const char CameraParameters::KEY_SUPPORTED_HFR_SIZES[] = "hfr-size-values";
const char CameraParameters::KEY_SUPPORTED_MEM_COLOR_ENHANCE_MODES[] = "mce-values";
const char CameraParameters::VIDEO_HFR_OFF[] = "off";
const char CameraParameters::VIDEO_HFR_2X[] = "60";
const char CameraParameters::VIDEO_HFR_3X[] = "90";
const char CameraParameters::VIDEO_HFR_4X[] = "120";
const char CameraParameters::KEY_VIDEO_HIGH_FRAME_RATE[] = "video-hfr";
const char CameraParameters::KEY_SUPPORTED_VIDEO_HIGH_FRAME_RATE_MODES[] = "video-hfr-values";
const char CameraParameters::KEY_HISTOGRAM[] = "histogram";
const char CameraParameters::KEY_SUPPORTED_HISTOGRAM_MODES[] = "histogram-values";
const char CameraParameters::HISTOGRAM_ENABLE[] = "enable";
const char CameraParameters::HISTOGRAM_DISABLE[] = "disable";
const char CameraParameters::SKIN_TONE_ENHANCEMENT_ENABLE[] = "enable";
const char CameraParameters::SKIN_TONE_ENHANCEMENT_DISABLE[] = "disable";
const char CameraParameters::KEY_SKIN_TONE_ENHANCEMENT[] = "skinToneEnhancement";
const char CameraParameters::KEY_SUPPORTED_SKIN_TONE_ENHANCEMENT_MODES[] = "skinToneEnhancement-values";
const char CameraParameters::DENOISE_OFF[] = "denoise-off";
const char CameraParameters::DENOISE_ON[] = "denoise-on";
const char CameraParameters::KEY_DENOISE[] = "denoise";
const char CameraParameters::KEY_SUPPORTED_DENOISE[] = "denoise-values";
const char CameraParameters::EFFECT_EMBOSS[] = "emboss";
const char CameraParameters::EFFECT_SKETCH[] = "sketch";
const char CameraParameters::EFFECT_NEON[] = "neon";
const char CameraParameters::SCENE_MODE_FLOWERS[] = "flowers";
const char CameraParameters::SCENE_MODE_AR[] = "AR";
const char CameraParameters::PIXEL_FORMAT_YUV420SP_ADRENO[] = "yuv420sp-adreno";
const char CameraParameters::PIXEL_FORMAT_RAW[] = "raw";
const char CameraParameters::PIXEL_FORMAT_YV12[] = "yuv420p";
const char CameraParameters::PIXEL_FORMAT_NV12[] = "nv12";
const char CameraParameters::EFFECT_CARTOONIZE[] = "cartoonize";
const char CameraParameters::EFFECT_POINT_RED_YELLOW[] = "point-red-yellow";
const char CameraParameters::EFFECT_POINT_GREEN[] = "point-green";
const char CameraParameters::EFFECT_POINT_BLUE[] = "point-blue";
const char CameraParameters::EFFECT_VINTAGE_COLD[] = "vintage-cold";
const char CameraParameters::EFFECT_VINTAGE_WARM[] = "vintage-warm";
const char CameraParameters::EFFECT_WASHED[] = "washed";
const char CameraParameters::SCENE_MODE_BACKLIGHT[] = "backlight";
const char CameraParameters::SCENE_MODE_ASD[] = "asd";

CameraParameters::CameraParameters()
                : mMap()
{
}

CameraParameters::~CameraParameters()
{
}

String8 CameraParameters::flatten() const
{
    String8 flattened("");
    size_t size = mMap.size();

    for (size_t i = 0; i < size; i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);

        flattened += k;
        flattened += "=";
        flattened += v;
        if (i != size-1)
            flattened += ";";
    }

    return flattened;
}

void CameraParameters::unflatten(const String8 &params)
{
    const char *a = params.string();
    const char *b;

    mMap.clear();

    for (;;) {
        // Find the bounds of the key name.
        b = strchr(a, '=');
        if (b == 0)
            break;

        // Create the key string.
        String8 k(a, (size_t)(b-a));

        // Find the value.
        a = b+1;
        b = strchr(a, ';');
        if (b == 0) {
            // If there's no semicolon, this is the last item.
            String8 v(a);
            mMap.add(k, v);
            break;
        }

        String8 v(a, (size_t)(b-a));
        mMap.add(k, v);
        a = b+1;
    }
}


void CameraParameters::set(const char *key, const char *value)
{
    if (key == NULL || value == NULL)
        return;

    // XXX i think i can do this with strspn()
    if (strchr(key, '=') || strchr(key, ';')) {
        //XXX ALOGE("Key \"%s\"contains invalid character (= or ;)", key);
        return;
    }

    if (strchr(value, '=') || strchr(value, ';')) {
        //XXX ALOGE("Value \"%s\"contains invalid character (= or ;)", value);
        return;
    }
#ifdef QCOM_HARDWARE
    // qcom cameras default to delivering an extra zero-exposure frame on HDR.
    // The android SDK only wants one frame, so disable this unless the app
    // explicitly asks for it
    if (!get("hdr-need-1x")) {
        mMap.replaceValueFor(String8("hdr-need-1x"), String8("false"));
    }
#endif

    mMap.replaceValueFor(String8(key), String8(value));
}

void CameraParameters::set(const char *key, int value)
{
    char str[16];
    sprintf(str, "%d", value);
    set(key, str);
}

void CameraParameters::setFloat(const char *key, float value)
{
    char str[16];  // 14 should be enough. We overestimate to be safe.
    snprintf(str, sizeof(str), "%g", value);
    set(key, str);
}

const char *CameraParameters::get(const char *key) const
{
    String8 v = mMap.valueFor(String8(key));
    if (v.length() == 0)
        return 0;
    return v.string();
}

int CameraParameters::getInt(const char *key) const
{
    const char *v = get(key);
    if (v == 0)
        return -1;
    return strtol(v, 0, 0);
}

float CameraParameters::getFloat(const char *key) const
{
    const char *v = get(key);
    if (v == 0) return -1;
    return strtof(v, 0);
}

void CameraParameters::remove(const char *key)
{
    mMap.removeItem(String8(key));
}

// Parse string like "640x480" or "10000,20000"
static int parse_pair(const char *str, int *first, int *second, char delim,
                      char **endptr = NULL)
{
    // Find the first integer.
    char *end;
    int w = (int)strtol(str, &end, 10);
    // If a delimeter does not immediately follow, give up.
    if (*end != delim) {
        ALOGE("Cannot find delimeter (%c) in str=%s", delim, str);
        return -1;
    }

    // Find the second integer, immediately after the delimeter.
    int h = (int)strtol(end+1, &end, 10);

    *first = w;
    *second = h;

    if (endptr) {
        *endptr = end;
    }

    return 0;
}

static void parseSizesList(const char *sizesStr, Vector<Size> &sizes)
{
    if (sizesStr == 0) {
        return;
    }

    char *sizeStartPtr = (char *)sizesStr;

    while (true) {
        int width, height;
        int success = parse_pair(sizeStartPtr, &width, &height, 'x',
                                 &sizeStartPtr);
        if (success == -1 || (*sizeStartPtr != ',' && *sizeStartPtr != '\0')) {
            ALOGE("Picture sizes string \"%s\" contains invalid character.", sizesStr);
            return;
        }
        sizes.push(Size(width, height));

        if (*sizeStartPtr == '\0') {
            return;
        }
        sizeStartPtr++;
    }
}

void CameraParameters::setPreviewSize(int width, int height)
{
    char str[32];
    sprintf(str, "%dx%d", width, height);
    set(KEY_PREVIEW_SIZE, str);
}

void CameraParameters::getPreviewSize(int *width, int *height) const
{
    *width = *height = -1;
    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_PREVIEW_SIZE);
    if (p == 0)  return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getPreferredPreviewSizeForVideo(int *width, int *height) const
{
    *width = *height = -1;
    const char *p = get(KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO);
    if (p == 0)  return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedPreviewSizes(Vector<Size> &sizes) const
{
    const char *previewSizesStr = get(KEY_SUPPORTED_PREVIEW_SIZES);
    parseSizesList(previewSizesStr, sizes);
}

void CameraParameters::setVideoSize(int width, int height)
{
    char str[32];
    sprintf(str, "%dx%d", width, height);
    set(KEY_VIDEO_SIZE, str);
}

void CameraParameters::getVideoSize(int *width, int *height) const
{
    *width = *height = -1;
    const char *p = get(KEY_VIDEO_SIZE);
    if (p == 0) return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedVideoSizes(Vector<Size> &sizes) const
{
    const char *videoSizesStr = get(KEY_SUPPORTED_VIDEO_SIZES);
    parseSizesList(videoSizesStr, sizes);
}

void CameraParameters::setPreviewFrameRate(int fps)
{
    set(KEY_PREVIEW_FRAME_RATE, fps);
}

int CameraParameters::getPreviewFrameRate() const
{
    return getInt(KEY_PREVIEW_FRAME_RATE);
}

void CameraParameters::getPreviewFpsRange(int *min_fps, int *max_fps) const
{
    *min_fps = *max_fps = -1;
    const char *p = get(KEY_PREVIEW_FPS_RANGE);
    if (p == 0) return;
    parse_pair(p, min_fps, max_fps, ',');
}

void CameraParameters::setPreviewFormat(const char *format)
{
    set(KEY_PREVIEW_FORMAT, format);
}

const char *CameraParameters::getPreviewFormat() const
{
    return get(KEY_PREVIEW_FORMAT);
}

void CameraParameters::setPictureSize(int width, int height)
{
    char str[32];
    sprintf(str, "%dx%d", width, height);
    set(KEY_PICTURE_SIZE, str);
}

void CameraParameters::getPictureSize(int *width, int *height) const
{
    *width = *height = -1;
    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_PICTURE_SIZE);
    if (p == 0) return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedPictureSizes(Vector<Size> &sizes) const
{
    const char *pictureSizesStr = get(KEY_SUPPORTED_PICTURE_SIZES);
    parseSizesList(pictureSizesStr, sizes);
}

void CameraParameters::setPictureFormat(const char *format)
{
    set(KEY_PICTURE_FORMAT, format);
}

const char *CameraParameters::getPictureFormat() const
{
    return get(KEY_PICTURE_FORMAT);
}

void CameraParameters::dump() const
{
    ALOGD("dump: mMap.size = %zu", mMap.size());
    for (size_t i = 0; i < mMap.size(); i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);
        ALOGD("%s: %s\n", k.string(), v.string());
    }
}

status_t CameraParameters::dump(int fd, const Vector<String16>& /*args*/) const
{
    const size_t SIZE = 256;
    char buffer[SIZE];
    String8 result;
    snprintf(buffer, 255, "CameraParameters::dump: mMap.size = %zu\n", mMap.size());
    result.append(buffer);
    for (size_t i = 0; i < mMap.size(); i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);
        snprintf(buffer, 255, "\t%s: %s\n", k.string(), v.string());
        result.append(buffer);
    }
    write(fd, result.string(), result.size());
    return NO_ERROR;
}

void CameraParameters::getSupportedPreviewFormats(Vector<int>& formats) const {
    const char* supportedPreviewFormats =
          get(CameraParameters::KEY_SUPPORTED_PREVIEW_FORMATS);

    if (supportedPreviewFormats == NULL) {
        ALOGW("%s: No supported preview formats.", __FUNCTION__);
        return;
    }

    String8 fmtStr(supportedPreviewFormats);
    char* prevFmts = fmtStr.lockBuffer(fmtStr.size());

    char* savePtr;
    char* fmt = strtok_r(prevFmts, ",", &savePtr);
    while (fmt) {
        int actual = previewFormatToEnum(fmt);
        if (actual != -1) {
            formats.add(actual);
        }
        fmt = strtok_r(NULL, ",", &savePtr);
    }
    fmtStr.unlockBuffer(fmtStr.size());
}

int CameraParameters::previewFormatToEnum(const char* format) {
    return
        !format ?
            HAL_PIXEL_FORMAT_YCrCb_420_SP :
        !strcmp(format, PIXEL_FORMAT_YUV422SP) ?
            HAL_PIXEL_FORMAT_YCbCr_422_SP : // NV16
        !strcmp(format, PIXEL_FORMAT_YUV420SP) ?
            HAL_PIXEL_FORMAT_YCrCb_420_SP : // NV21
        !strcmp(format, PIXEL_FORMAT_YUV422I) ?
            HAL_PIXEL_FORMAT_YCbCr_422_I :  // YUY2
        !strcmp(format, PIXEL_FORMAT_YUV420P) ?
            HAL_PIXEL_FORMAT_YV12 :         // YV12
        !strcmp(format, PIXEL_FORMAT_RGB565) ?
            HAL_PIXEL_FORMAT_RGB_565 :      // RGB565
        !strcmp(format, PIXEL_FORMAT_RGBA8888) ?
            HAL_PIXEL_FORMAT_RGBA_8888 :    // RGB8888
        !strcmp(format, PIXEL_FORMAT_BAYER_RGGB) ?
            HAL_PIXEL_FORMAT_RAW16 :   // Raw sensor data
        -1;
}

bool CameraParameters::isEmpty() const {
    return mMap.isEmpty();
}

// Custom parameters for Samsung
int CameraParameters::getInt64(const char *key __unused) const
{
    return -1;
}

const char * CameraParameters::getPreviewFrameRateMode() const
{
    return mParams->get("preview-frame-rate-mode");
}

void CameraParameters::setPreviewFrameRateMode(const char *mode)
{
    mParams->set("preview-frame-rate-mode", mode);
}

void CameraParameters::getMeteringAreaCenter(int *x, int *y) const
{
    const char *p;
    *x = *y = -2000;
    p = mParams->get("metering-areas");
    parse_pair(p, x, y, 'x');
    *x /= 2;
    *y /= 2;
}

void CameraParameters::setTouchIndexAec(int x, int y)
{
    char buf[32];
    snprintf(buf, 32, "%dx%d", x, y);
    mParams->set("touch-index-aec", buf);
}

void CameraParameters::setTouchIndexAf(int x, int y)
{
    char buf[32];
    snprintf(buf, 32, "%dx%d", x, y);
    mParams->set("touch-index-af", buf);
}

void CameraParameters::setPreviewFpsRange(int min, int max)
{
    char buf[32];
    snprintf(buf, 32, "%d,%d", min, max);
    mParams->set("preview-fps-range", buf);
}

}; // namespace android
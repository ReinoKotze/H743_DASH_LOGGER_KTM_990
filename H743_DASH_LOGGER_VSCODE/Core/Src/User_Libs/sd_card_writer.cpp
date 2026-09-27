#include "INCLUDES.hpp"

uint32_t SD_Card_WriteFile(const char *path,
                           const void *data,
                           uint32_t length,
                           bool append)
{
    FIL file;
    FRESULT result;
    FRESULT close_result = FR_OK;
    UINT bytes_written = 0U;
    bool file_opened = false;

    if ((path == nullptr) || ((data == nullptr) && (length != 0U)))
    {
        return static_cast<uint32_t>(FR_INVALID_PARAMETER);
    }

    result = f_mount(&SDFatFS, SDPath, 1U);
    if (result != FR_OK)
    {
        return static_cast<uint32_t>(result);
    }

    const BYTE mode = append
        ? static_cast<BYTE>(FA_OPEN_ALWAYS | FA_WRITE)
        : static_cast<BYTE>(FA_CREATE_ALWAYS | FA_WRITE);

    result = f_open(&file, path, mode);
    if (result == FR_OK)
    {
        file_opened = true;
    }
    if ((result == FR_OK) && append)
    {
        result = f_lseek(&file, f_size(&file));
    }

    if ((result == FR_OK) && (length != 0U))
    {
        result = f_write(&file, data, static_cast<UINT>(length), &bytes_written);
        if ((result == FR_OK) && (bytes_written != static_cast<UINT>(length)))
        {
            result = FR_DISK_ERR;
        }
    }

    if (result == FR_OK)
    {
        result = f_sync(&file);
    }

    if (file_opened)
    {
        close_result = f_close(&file);
    }
    if ((result == FR_OK) && file_opened)
    {
        result = close_result;
    }

    (void)f_mount(nullptr, SDPath, 0U);
    return static_cast<uint32_t>(result);
}

uint32_t SD_Card_WriteText(const char *path,
                           const char *text,
                           bool append)
{
    if (text == nullptr)
    {
        return static_cast<uint32_t>(FR_INVALID_PARAMETER);
    }

    return SD_Card_WriteFile(path, text,
                             static_cast<uint32_t>(strlen(text)), append);
}

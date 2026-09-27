#ifndef SD_CARD_WRITER_HPP
#define SD_CARD_WRITER_HPP

#include <cstdint>

uint32_t SD_Card_WriteFile(const char *path,
                           const void *data,
                           uint32_t length,
                           bool append);

uint32_t SD_Card_WriteText(const char *path,
                           const char *text,
                           bool append);

#endif /* SD_CARD_WRITER_HPP */

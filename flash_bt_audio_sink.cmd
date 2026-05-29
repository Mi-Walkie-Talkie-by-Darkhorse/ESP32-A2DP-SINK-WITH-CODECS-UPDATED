cd /d %~dp0esp-idf
call export.bat
cd /d %~dp0bt_audio_sink\build
python -m esptool --chip esp32 -p COM6 -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_size 8MB --flash_freq 80m 0x110000 bt_audio_sink.bin 0x610000 ota_data_initial.bin

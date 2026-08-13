@echo off
cd /d "D:\Alex\ESP32-A2DP-SINK-WITH-CODECS-UPDATED\esp-idf"
call export.bat
cd /d "D:\Alex\ESP32-A2DP-SINK-WITH-CODECS-UPDATED\bt_audio_sink"
idf.py flash -p COM3 monitor
pause

# esp32-snmp-oled

For now this is just a simple firmware that displays anything received through
UDP on the OLED display. I have made a simple script that will push some
system stats to the ESP32 using `nc`

## Script parameters:

1. IP address of the ESP32
2. Port of the ESP32 (6060)
3. Name of the wired interface (enp* usually)
4. Name of the wireless interface (wlp* usually)
5. Path to get free space for

## Example:

    CPU: 18%
    Used mem: 3125M
    /home free: 18G
    Disk : 0t/s
    Wired: 0.00%
    Wifi: 0.00%

## Values:

1. CPU utilisation
2. Used memory.
3. Free disk space at path
4. Disk IO transfers per second
5. Wired network interface utilisation
6. Wireless network interface utilisation
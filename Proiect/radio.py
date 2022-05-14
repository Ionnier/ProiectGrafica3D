import os
os.add_dll_directory(r'C:\Program Files\VideoLAN\VLC')

import vlc
import time
import sys

#'http://asculta.radiotaraf.ro:7100/'

#define VLC instance
instance = vlc.Instance('--input-repeat=-1', '--fullscreen')

#Define VLC player
player=instance.media_player_new()

#Define VLC media
media=instance.media_new(sys.argv[1])

#Set player media
player.set_media(media)

#Play the media
player.play()

while True:
  pass
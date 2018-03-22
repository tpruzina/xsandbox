#!/bin/sh

set -eu

# this is where we will save the cookie used to identify this untrusted session
cookie=/tmp/.Xauthority-$USER-$$-untrusted
# create file and set its permissions so that other users can't read it, very important
touch "$cookie"
chmod 0600 "$cookie"
# we use xauth to put an untrusted cookie into this file, Xorg will be able to identify the client is untrusted due to this cookie's contents
xauth -f "$cookie" generate "$DISPLAY" MIT-MAGIC-COOKIE-1 untrusted
# the XAUTHORITY environment variable is used by xlib to point to the cookie we are using
export XAUTHORITY="$cookie"
# and just exec into the actual program
exec "$@"


Installation on Ubuntu:

apt-get install g++ make isc-kea-dev libboost-dev libboost-system-dev
make
make DESTDIR=/usr/lib/x86_64-linux-gnu/kea/hooks install

Then add the hook to your kea-dhcp4.conf:

     "hook-libraries": [
         // ....
         {
             "library": "/usr/lib/x86_64-linux-gnu/kea/hooks/libdhcp_cisco_link_selection_to_rfc3527.so"
         }
         // ....
     ]

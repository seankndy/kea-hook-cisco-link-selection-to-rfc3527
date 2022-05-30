This Kea hook creates the RFC3527 "link-selection" RAI sub-option 5 from Cisco's proprietary link-selection sub-option 151.

Kea uses the RFC3527 sub-option during subnet selection, but it does not use Cisco's sub-option 151 hence the reason for this hook.  It saves you from having to create custom client-classes for every subnet.


Installation on Ubuntu:

```
$ sudo apt-get install g++ make isc-kea-dev libboost-dev libboost-system-dev
$ make
$ sudo make DESTDIR=/usr/lib/x86_64-linux-gnu/kea/hooks install
```

Then add the hook to your kea-dhcp4.conf:

     "hook-libraries": [
         // ....
         {
             "library": "/usr/lib/x86_64-linux-gnu/kea/hooks/libdhcp_cisco_link_selection_to_rfc3527.so"
         }
         // ....
     ]

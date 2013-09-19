Description
-----------------
Simple module, which allows to flag Nodes as another users. After installation
of module it is necessary to configure which flags could be used. Flags are
configurable on the operation level (flag / unflag). After The flag has proper
setup, the module functionality will appear on node detail.

TODO
-----------------
* Support for other entities.
* Move from content suffix to better place.
* Flag remove - variable cleanup.
* Respect flag / unflag permission of original flag.
* Respect if user may flag content of other users in autocomplete.
* Realname support.
* List Global flags in module settings- Explanation why are not listed.
* Solve page callback paths in better way (infinite loop in autocomplete if flag-as prefix was used- "fa" prefix fixed that for now.).
* If The flag may be used for authenticated user, admin user will be visible in autocomplete.
* Flag As / Unflag As configurable labels.
# MCServerHandler
A headless library for handling minecraft servers. Coded in C 🤮 because I wanted people to be able to make a wrapper in basically any language using their method for including C code.

Has special json data to have attributes on the servers and the worlds, the file structure is like this.

also all the server properties and .json files where moved to be a part of the world data, instead of whitelist, banned-list and everything else being per server it's now per world

worlds{
  name (ID){
    yyyy-mm-dd_hh-mm #actual world file with timestamp with the time it was saved
    yyyy-mm-dd_hh-mm #same world but different time
    banned-ips.json
    banned-players.json
    ops.json
    server.properties
    whietlist.json
    world.json #my own custom data, I will upload some example data
  }
  name (ID) #will contain same as other folder
  name (ID)
}

servers{
  name (ID){
  all the server files with an added start.sh script and start.bat script, might switch this out to be a start.lua script with embedded lua in my project
  }
}

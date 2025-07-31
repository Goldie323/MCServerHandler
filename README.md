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



Also this is somewhat far from being finished and I don't have a full plan, I have all the functions I want to implement planned but I'm not sure fully how I want to implement some of them but I am kind of thinking of just getting a working version out there and then I can change things that I want to change. Like I have an idea that backing up the world or saving the world could have a lua script that is run and so if someone wanted to make a delta encoded backup system they could or if they wanted to do any other form of backups that are special or different, but they would also have to make a function to get the world back from however they saved it and so just a few ideas like that to make it modular and make it so that the user can change out some functionality.

Another idea is that with how much speed isn't a needed thing for this I could easily just make it so that it's basically entirely coded in lua with a C base library that exposes some system calls and stuff that I feel like would be bad to do in lua and so I'd write a simple C script that uses unistd.h and other posix complient stuff to handle things and then you can also make windows versions of the functions using simple ifndef logic, but for now I'm not dealing with windows and I also kind of want to finish this first before continuing to come up with new ideas like this.

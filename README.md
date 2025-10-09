This a Chat based on peer to peer, with anonymous names yet need the ip from both of the persons (or more eventually) to chat, is on terminal, so all the messages wont be saved
when the server ends the connection(the person)
how to set up:
-The person who wants to set a chat with another person needs to specify the next command main -S (your ip) -P (your port) -K (the key that the client will need to connect to your server)
this will set up a server where you and the other person can chat for unlimited time, and you just need to press Ctrl + C to end the life connection and the chat will be closed for both of yall
-In case you want to set up for a group of persons, first of all you will need to specify the next command main -S (your ip) -P (your port) -All
with this command you will be saying: "Hey, create a server with this ip and port, but, do not wait for a key, just let them join". Is a feature that may not be secure but exists

Why a key? well, is because i like keys.
Why peer to peer? well, because, our chats are getting too public, there's no privacy, with this tool you can chat your private things with your mate
Why on terminal? Because i dont know how to use Qt for C++, besides is my first kinda program based con UDP protocols for chats, where the speed is greater than quality
Why udp and not TCP? Well like i said before, i like speed, i dont care if my message got like a fucking HASH is not my bussiness to decrypt that bullshit, is yours
Why are you coding this? I'm bored, i don't know that to do with my life and, at least, i wanna develop a tool that a few folks will use



HOW TO SET UP A CLIENT:
First you will notice there's two files in src: A key file and a server file. The key file is YOUR personal file to set up a server, this can be used for server-side to set up a limited group of persons who can send message to the same server under the same key typed in that file. Then you'd have the SERVER file, this file will be used to SEND AND SAVE SERVERS, what does it mean?, well, you might wanna be receive message from other but you may also wanna send message to others, thats what SERVER stands for, the key in the other file is to set up your own server config, but the SERVER file is to set up YOUR CREDENTIALS as a client, you can even connect to your own server with those configs typed in the server file.

Now, how do i set up a client?, first of all, you will need to specify the servers and their ports that you wanna be connected and send the message, you can send 1 message to ALL those servers, or if you want to send it to just one, then you will need to specify that into the SERVER file. How do i save servers? use this format:
xxx.xxx.xxx.x:xxxx
yyy.yyy.yyy.y:yyyy
zzz.zzz.zzz.z:zzzz
myusername:key
this format will allow you to setup the server that you will be sending the message to, and the key? well, that will be after the program evaluates how many servers you will be sending the message, meaning? if you have 1 server, then the password have to be after the last server. Otherwise, you wouldn't sending anything.


Commands line to setup a server:
-S[IPV4]  --Setups a server with a IPV4 address required
-P[PORT]  --Setups the port, cant be blank otherwise, you will be getting an error
-K        --Setups the key for the server, this key will be validated from your key file
-A        --Setups an AUTO server, this means that the program will be using any ipv4 and any port and any key


Commands line to setup the client: 
-M        --Setups the message that you will be sending, in other words, that would be your message
-C        --Setups the config to send the message to the server, you will be needing to specify the route of
            server file, this means that the message will be sended to those servers with that username 


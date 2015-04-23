#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <pthread.h>
#include <sstream>
#include <utility>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>      // Needed for the socket functions
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
 #include <errno.h>
 #include <sys/stat.h>  //needed for open
#include <fcntl.h>     //needed for open
#define BACKLOG	10
#define BUF_SIZE	1024
#define LISTEN_PORT 8888
#define HTTP_PORT	80

using namespace std;
//#define SERVER_IP   "0.0.0.0"
int threadCount = BACKLOG; // total number of users the server will allow communication
void *client_handler(void *arg);
int main(int argc, char *argv[]) {
	// Declaration of variables for socket programing
	int status, *sock_tmp;
	pthread_t a_thread;
	void *thread_result;
	struct sockaddr_in addr_mine;
	struct sockaddr_in addr_remote;
	int sock_listen;
	int sock_aClient;
	int addr_size;
	int reuseaddr = 1;

	//Socket binding
	sock_listen = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_listen < 0) {
		perror("socket() failed");
		exit(0);
	}
	// Address settings includind IP, PORT NUMBER
	memset(&addr_mine, 0, sizeof(addr_mine));
	addr_mine.sin_family = AF_INET;
	addr_mine.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_mine.sin_port = htons((unsigned short)LISTEN_PORT);
	//Check Port number status
	status = bind(sock_listen, (struct sockaddr *) &addr_mine,
		sizeof(addr_mine));
	if (status < 0) {
		perror("bind() failed");
		close(sock_listen);
		exit(1);
	}
	// Listen port number
	status = listen(sock_listen, 5);
	if (status < 0) {
		perror("listen() failed");
		close(sock_listen);
		exit(1);
	}

	addr_size = sizeof(struct sockaddr_in);
	printf("waiting for a client\n");
	//Thread Creation block
	while (1) {
		if (threadCount < 1) {
			sleep(1);
		}

		sock_aClient = accept(sock_listen, (struct sockaddr *) &addr_remote,
			(socklen_t*)&addr_size);
		if (sock_aClient == -1){
			close(sock_listen);
			exit(1);
		}

		printf("Got a connection from %s on port %d\n",
			inet_ntoa(addr_remote.sin_addr),
			htons(addr_remote.sin_port));
		sock_tmp = (int*)malloc(1);
		*sock_tmp = sock_aClient;
		printf("thread count = %d\n", threadCount);
		threadCount--;
		status = pthread_create(&a_thread, NULL, client_handler,
			(void *)sock_tmp);
		if (status != 0) {
			perror("Thread creation failed");
			printf("In client_handler ERROR \n");
			close(sock_listen);
			close(sock_aClient);
			free(sock_tmp);
			exit(1);
		}
	}
	return 0;


}
// function each created thread compute
void *client_handler(void *sock_desc) {
    // 3. Define a table of blocking websites records using an STL map
std::map<int, std::string> g_mapwebRecords;
            g_mapwebRecords.insert(std::pair<int, std::string> (1, "www.facebook.com") );//insert
			g_mapwebRecords.insert(std::pair<int, std::string> (2, "www.youtube.com") );//insert
			g_mapwebRecords.insert(std::pair<int, std::string> (3, "www.hulu.com") );//insert
			g_mapwebRecords.insert(std::pair<int, std::string> (4, "www.virus.com") );//insert
int msg_size,j;
	char buf[BUF_SIZE],line[1];
	//int text;
	int sock = *(int*)sock_desc; //socket initialization
	char *token;
	std::string buf1;
while(1){
	if (recv(sock, buf, BUF_SIZE, 0)<0){
		//ERROR_RESPONSE
	}
	if (strcmp(buf,"")==0){
		close(sock);
	}
	printf(" FIRST THING FIRST %s\n", buf);
	/* get the first token */
	token = strtok(buf, "/ HTTP");
	printf(" SECOND THING FIRST %s\n", token);
	/* walk through other tokens */

		token = strtok(NULL, "/ HTTP");

		bool exist,checkin = false;
		std::string extension = ".txt";
        std::string extension1="";
		int len = strlen(token) + extension.length()+1;
		int len1=strlen(token)+extension1.length()+1;
        char weblink[len1];
		char  url[len];
		strcpy(weblink,token);
		strcpy(url, token);
		 strcat (url,extension.c_str());
		 strcat (weblink,extension1.c_str());
		 printf(" THIRD THING FIRST %s\n", url);
		// allocate memory to contain file data
		char* buffer = new char[BUF_SIZE];
		//std::ifstream ifs(url, std::ifstream::binary);
        std::ifstream infile(url);

		// get pointer to associated buffer object
		//std::filebuf* pbuf = infile.rdbuf();
		if (infile.good()==false){
			exist = false;
			printf(" EXIST FIRST-FALSE %d\n", exist);
		}
		else{
			exist = true;
			printf(" EXIST FIRST-TRUE %d\n", exist);
		}

		//File exist in cache
		if (exist == true){
          msg_size= open(url, O_RDWR);
           printf(" CACHED OPEN ERRNO %d\n", errno);
     while (read(msg_size,line,1)>0)
    {
     j=write(sock,line,1);
     // printf(" CACHED write ERRNO %d\n", errno);
     // printf(" CACHED DATA %s\n",line);

     }

  infile.close();
  j=close(msg_size);
 // close(sock);
 // free(sock_desc);
 // exit(1);
			// get file size using buffer's members
//			std::size_t size = pbuf->pubseekoff(0, infile.end, infile.in);
//			pbuf->pubseekpos(0, infile.in);
//			// get file data
//			pbuf->sgetn(buffer, size);
//			infile.close();
//			if (send(sock, buffer,size , 0) < 0){
//
//			}
		}
		//file not in cache
		if (exist == false){
    for (std::map<int, std::string>::iterator it = g_mapwebRecords.begin(); it != g_mapwebRecords.end(); ++it)
    {
       std::cout<<  it->second.c_str() << "  value of checkin true"<<'\n';
//		if(it->second.c_str()==token){
//			checkin==true;
//		}
        if(strcmp(it->second.c_str(),weblink)==0){
			checkin==true;
			weblink="www.cnet.edu"
			// break;
			msg_size= open("blocking.text", O_RDWR);
           printf(" CACHED OPEN ERRNO %d\n", errno);
     while (read(msg_size,line,1)>0)
    {
     j=write(sock,line,1);
     // printf(" CACHED write ERRNO %d\n", errno);
     // printf(" CACHED DATA %s\n",line);

     }
     //close(sock);
     break;
		}

    }
	if(checkin==false){
			int sock_send;
			struct sockaddr_in	addr_send ;
			struct addrinfo hints,*servinfo,*p;
			int	i, text;
			int	send_len, bytes_sent;
			char  buff[BUF_SIZE];//contain temporary file name request
			//TODO CONNECT TO HTTP 80
			int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
//int sock;
struct sockaddr_in client;
int PORT = 80;
			/* Obtain address(es) matching host/port */

          struct hostent * host = gethostbyname(weblink);

    if ( (host == NULL) || (host->h_addr == NULL) ) {
        cout << "Error retrieving DNS information." << endl;
        //close(sock_send);
        exit(1);
    }

    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons( PORT );
    memcpy(&client.sin_addr, host->h_addr, host->h_length);

    sock_send = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_send < 0) {
        cout << "Error creating socket." << endl;
        close(sock_send);
        exit(1);
    }

    if ( connect(sock_send, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        close(sock_send);
        cout << "Could not connect" << endl;
        exit(1);
    }


			/* create socket for sending data */
//		sock_send = socket(AF_INET, SOCK_STREAM, 0);
//			if (sock_send < 0) {
//				printf("socket() failed\n");
//				exit(0);
//			}
//
//			/* create socket address structure to connect to */
//			memset(&addr_send, 0, sizeof(addr_send)); /* zero out structure */
//			addr_send.sin_family = AF_INET; /* address family */
//			if(send_len=getaddrinfo(weblink,"http",&hints,&servinfo)!=0){
//                printf(" GET-ADDRESS-INFO %s\n",gai_strerror(send_len));
//			}
//			for(p=servinfo;p!=NULL ;p=p->ai_next){
//                add_send=(struct sockaddr_in )p->ai_addr;
//                strcpy()
//
//			}
//			 addr_send.sin_addr.s_addr = inet_addr(weblink);
//            addr_send.sin_port = htons((unsigned short)HTTP_PORT);
//
//			//addr_send.sin_addr.s_addr = htonl(INADDR_ANY);
//			std::string lookup=weblink;
//			//lookup.replace(0,4,"GET http://" );
//			//lookup=""+lookup+" HTTP/1.0\n\n";
//			//lookup.replace(0,4,"");
//			printf(" TEST LOOKUP %s\n", lookup.c_str());
		//	addr_send.sin_addr.s_addr = inet_addr(lookup.c_str());
			//addr_send.sin_addr.s_addr = inet_addr(SERVER_IP);
			//addr_send.sin_port = htons((unsigned short)HTTP_PORT);

/*int statu;
  struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
  struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

  // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
  // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
  // is created in C++, it will be given a block of memory. This memory is not necessary
  // empty. Therefor we use the memset function to make sure all fields are NULL.
  memset(&host_info, 0, sizeof host_info);

  std::cout << "Setting up the structs..."  << std::endl;

  host_info.ai_family =  AF_INET;     // IP version not specified. Can be both.
  host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

  // Now fill up the linked list of host_info structs with google's address information.
  statu = getaddrinfo(weblink, "80", &host_info, &host_info_list);
  // getaddrinfo returns 0 on succes, or some other value when an error occured.
  // (translated into human readable text by the gai_gai_strerror function).
  if (statu != 0)  std::cout << "getaddrinfo error" << gai_strerror(statu) ;
  std::cout << "Creating a socket..."  << std::endl;
int socketfd ; // The socket descripter
socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
host_info_list->ai_protocol);
if (socketfd == -1)  std::cout << "socket error " ;
std::cout << "Connect()ing..."  << std::endl;
statu = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
if (statu == -1)  std::cout << "connect error" ;
 printf(" STATU %d\n", statu);
 */
//	/*		 connect to the HTTP Socket  */
//			i = connect(sock_send, (struct sockaddr *) &addr_send, sizeof(addr_send));
//			if (i < 0) {
//                    printf(" TEST ADDR %d\n", errno);
//				printf("connect() failed\n");
//				close(sock_send);
//				exit(0);
//			}
//Check Port number status
//	int statu = bind(text, (struct sockaddr *) &addr_send,
//		sizeof(addr_send));
//	if (statu < 0) {
//		perror("bind()text failed");
//		close(text);
//		exit(1);
//	}
//	// Listen port number
//	statu = listen(text, 5);
//	if (statu < 0) {
//		perror("listen()text failed");
//		close(text);
//		exit(1);
//	}
//			std::string word=weblink;
//			//word.replace(0,4,"GET http://www." );
//			//word=""+word+" HTTP/1.0\n\n";
//			//word.replace(0,4,"GET http://www." );
//			word.replace(0,4,"GET /www." );
//		   //word=word+" HTTP/1.1\r\nAccept: text/html, application/xhtml+xml, */*\r\nConnection: Keep-Alive\r\n\r\n";
//			word="GET / HTTP/1.1\r\n\r\n";
//			const char *msg =word.c_str();
//			//std::cout << word ;
//			 printf(" WEBLINK THING FIRST11 %s\n", msg);
//			 std::string response;
//			if (send(sfd, msg,sizeof(msg) , 0) < 0){
//                printf(" TEST SEND ERRNO %d\n", errno);
//			}
//			 // allocate memory for file content
//            printf(" SENT %d\n",1);
//			char incoming_data_buffer[9000];
//			if(recv(sfd,incoming_data_buffer,sizeof(incoming_data_buffer), 0)<=0){
//         printf(" TEST RECV ERRNO %d\n", errno);
//    }
// printf(" WEBLINK THING RESPONSE %s\n", incoming_data_buffer);

//			if(write(sock_send,word,sizeof(word))==-1){

		//	}
  stringstream ss;
    ss << "GET / HTTP/1.1\r\n"
       << "host:"<<weblink<<"\r\n"
       << "Accept: text/html,application/json\r\n"
       << "\r\n\r\n";
    string request = ss.str();

    if (send(sock_send, request.c_str(), request.length(), 0) != (int)request.length()) {
        cout << "Error sending request." << endl;
        exit(1);
    }

    char cur[1];
        std::streambuf *psbuf1, *backup1;
 	 std::fstream filestr1;
 	// int fdB = open(url, O_CREAT | O_RDWR, 0644);
 	 filestr1.open(url,std::fstream::in | std::fstream::out | std::fstream::app);
 	  //printf(" TEST OPEN ERRNO %d\n", errno);
	 // write to outfile
	// filestr1<<std::cout;
//	  while ( read(sock_send, &cur, 1) != 0 ) {
//       filestr1<<cur;
//    }
//int k=0;
    while ( read(sock_send,cur, 1) != 0 ) {
       // cout << cur;
         filestr1<<cur;
         text=write(sock,cur,1);
//         if(k==10)
//            break;
//        k++;

    }
// char cur[1];
printf(" TEST 1 ERRNO %d\n", errno);
//close(sock_send);
printf(" TEST 2 ERRNO %d\n", errno);
  close(sock);
//string response;
//   // ifstream myfile ("example.txt");
//    if (filestr1.is_open())
//    {
////        while ( getline(filestr1, response) ){
////          if (send(sock,response.c_str(),response.length() , 0) < 0){
////printf(" TEST SEND ERRNO %d\n", errno);
////			}
//// get pointer to associated buffer object
//		std::filebuf* pbuf1 = filestr1.rdbuf();
//		printf(" TEST READ ERRNO %d\n", errno);
//		// get file size using buffer's members
//			std::size_t size = pbuf1->pubseekoff(0, filestr1.end, filestr1.in);
//			pbuf1->pubseekpos(0, filestr1.in);
//			// get file data
//
//			pbuf1->sgetn((char*)&response, size);
//			printf(" TEST RESPONSE ERRNO %d\n", errno);
//text=write(sock,response,size);
//
//        filestr1.close();
//    }
//    else
//    {
//        cout << "Unable to open file";
//    }
  //filestr1.write(msg,strlen(msg)) ;
 // printf(" TEST WRITE ERRNO %d\n", errno);
 // filestr1<<incoming_data_buffer;

// // get pointer to associated buffer object
//		std::filebuf* pbuf1 = filestr1.rdbuf();
//		printf(" TEST READ ERRNO %d\n", errno);
//		// get file size using buffer's members
//			std::size_t size = pbuf1->pubseekoff(0, ifs.end, ifs.in);
//			pbuf1->pubseekpos(0, ifs.in);
//			// get file data
//
//			pbuf1->sgetn((char*)&response, size);
//			printf(" TEST buffer ERRNO %d\n", errno);
//			printf(" TEST buffer ERRNO %d\n", errno);
//  filestr1.close();
//freeaddrinfo(host_info_list);


 // delete &response;
 // delete &word;

  // char b[1];
//   int fdA = open(url,O_RDWR);
//    int n_char=0;
   //Use the read system call to obtain fdA one byte at time
  // while (read(fdA, b, 1)!=0)
  //  {
    // n_char=write(fdB,buffer,1);

  //   }


//  	//filestr.open (url);
////backup = std::cout.rdbuf();     // back up cout's streambuf
//	 psbuf1 = filestr1.rdbuf();        // get file's streambuf
//  	std::cout.rdbuf(psbuf1);         // assign streambuf to cout
//////  iterate over the map



			//send a connection request
			//bytes_sent = send(sock_send, buff, BUF_SIZE, 0);
			//if (bytes_sent < 0){

			//}

		//	int fdB = open("/home/knk0055/public_html/text51.txt", O_CREAT | O_RDWR, 0644);

}
if(checkin==true){
//char block[]="blocking.text";
printf(" Blocking website \n");
   msg_size= open("blocking.text", O_RDWR);
           printf(" CACHED OPEN ERRNO %d\n", errno);
     while (read(msg_size,line,1)>0)
    {
     j=write(sock,line,1);
     // printf(" CACHED write ERRNO %d\n", errno);
     // printf(" CACHED DATA %s\n",line);

     }
    // close(sock);
//buf1.append(token);
//if (send(sock,&buf1, buf1.length(), 0) < 0){
//				//TODO error  CNP_ACCONT_MESSAGE
//        }
//		}
	}
//	delete &exist;
//	delete buffer;
//	delete &checkin;
//	delete &url;
	//close(sock_send);

close(sock);
//free(sock_desc);
threadCount++;
}
}
}

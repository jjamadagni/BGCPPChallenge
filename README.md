# BGCPPChallenge
CPP Challenge


1. This is a simple program to convert a XSD in to An XML, and if needed converting the obtained XML in to a JSON file, and also validating the obtained XML with the Given XSD.

2. First the user need to install the docker. [Note: if the docker does not start, make sure VIrtualization is enabled in the BIOS menu].

3. Now clone the code and program to a local machine. once cloned copy all the files to the container directory by using the command,
   
   '''
   $ docker cp <File_name> <Container_name>: /<File_name>
  '''
  
4. Once all the files are copied, make sure to install the libraries that are required for the code to function.
  a. The first one is Tinyxml. TO install this, in the command line type 
     $ apt-get update
     $ apt-get install libtinyxml-dev  
     
  b. The second one is Xerces for the validation.
     $ apt-get install libxerces-c-dev
     
     
5. Once the libraries are installed and the files are added to the container, enter the container by using the following command

     $ docker exec -it <container_name> /bin/bash
     
6. once in the container build the code by following the command,

     $ g++ main.cpp -o main -ltinyxml -lxerces-c
     
7. once the code is compiled, run the application with the following command

     $ ./main <Name_of_the_XSD_file>
     
     
8. Now there will appear a menu asking you for different options, so select the option that you want to perform.

<center><h1> minipipe </h1></center>
<center><h2>This program mimics the behavior of the Unix pipe.</h2>
  <h3>Usage:</h3>
</center>

  ```bash
  ./pipex inputfile cmd1 ... cmdn outputfile
  ```
  this equals the behavior of 
  ```bash
  < inputfile cmd | ... | cmdn > outputfile
  ```
  #### heredoc:
  ```bash
  ./pipex here_doc limiter cmd1 ... cmdn outputfile
  ```

  this equals the behavior of 
  ```bash
  << limiter cmd | ... | cmdn > outputfile
  ```

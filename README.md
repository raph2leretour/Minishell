# Minishell
### Lexer <br>
input: readline output <br>
output: tokenized linked list <br>

```
$minishell echo "hello      hello" how are 'you 'doing? $USER |wc -l >outfile
```
Result: <br>

```
Token value: echo ;Token type: 1
Token value: "hello          hello" ;Token type: 1
Token value: how ;Token type: 1
Token value: are ;Token type: 1
Token value: 'you 'doing? ;Token type: 1
Token value: $USER ;Token type: 1
Token value: | ;Token type: 4
Token value: wc ;Token type: 1
Token value: -l ;Token type: 1
Token value: > ;Token type: 2
Token value: outfile ;Token type: 1
```

### Syntax analyzer <br>
input: tokenized linked list <br>
output: 1. in case of no syntax error -> same tokenized list <br>
2. in case of syntax error -> printed error type <br>

### Get simple commands for exec: <br>

```
cmds:
	cmd 1:
		infile: 0 (default)
		outfile: 1 (redirected to pipe)
		full_path: NULL (because echo is a builtin)
		full_cmd: {echo, hello hello, how, are, you doing?, pixel, NULL}
	cmd 2:
		infile: 0 (contains output of previous command)
		outfile: 3 (fd corresponding to the open file 'outfile')
		full_path: /bin/wc
		full_cmd: {wc, -l, NULL}
```

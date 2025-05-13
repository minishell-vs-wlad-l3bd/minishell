
if we remov path /bin/ls this will be work

export : ds="s"
export : ds+="s"
export : ds-="s"
export : sdhh
minishell ▶ unset PATH
minishell ▶ LS
minishell: LS: command not found
minishell ▶ ls
minishell: ls: command not found
minishell ▶ /bin/ls
minishell: /bin/ls: command not found
minishell ▶ mkdir -p a/s/d/f
minishell: mkdir: command not found
minishell ▶ 
minishell ▶ 
exit
➜  minishell git:(main) ✗ ./minishell
minishell ▶ mkdir -p a/s/d/f
minishell ▶ 
minishell ▶ cd  a/s/d/f
minishell ▶ pwd
/mnt/homes/mohidbel/Desktop/minishell/a/s/d/f
minishell ▶ rm -fr ../../../../a
minishell ▶ pwd
minishell ▶ cd ..
minishell: cd: No such file or directory
minishell ▶ env | grep PWD
PWD=/mnt/homes/mohidbel/Desktop/minishell/a/s/d/f
OLDPWD=/mnt/homes/mohidbel/Desktop/minishell
minishell ▶ cd -
minishell: cd: No such file or directory
minishell ▶ 

minishell ▶ export ddd="       "
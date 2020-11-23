#!/bin/bash

# #-----------------
# # 注释：1213 test
# #-----------------
# echo "test shell"

# vars=(1 2 34 5)
# echo "数组所有值:"
# echo ${vars[@]}
# echo ${vars[*]}

# echo "数组大小:"
# echo ${#vars[@]}
# echo ${#vars[*]}

# echo "单个元素的长度:"
# echo ${#vars[0]}
# echo ${#vars[2]}

# echo "外部传参:"
# echo "执行文件名: $0"
# echo "第一个参数: $1"
# echo "第二个参数: $2"
# echo "第三个参数: $3"

# echo "参数\$#: $#"
# echo "参数\$*: $*"
# echo "参数\$$: $$"
# echo "参数\$!: $!"
# echo "参数\$@: $@"
# echo "参数\$-: $-"
# echo "参数\$?: $?"

# echo "\$* 的传入结构:"
# for i in "$*"; do
# 	echo $i
# done

# echo "\$@ 的传入结构:"
# for i in "$@"
# do
# 	echo $i
# done

# echo "运算符:"
# val=`expr 2 + 2`
# echo "expr 2 + 2 = $val"

# a=10
# b=20

# # !!!
# val=`expr $a + $b`
# echo "a + b: $val"

# val=`expr $a - $b`
# echo "a - b: $val"

# val=`expr $a \* $b`
# echo "a * b: $val"

# val=`expr $a / $b`
# echo "a / b: $val"

# val=`expr $a % $b`
# echo "a % b: $val"

# if [ $a == $b ]
# then
# 	echo "a 等于 b"
# fi

# if [ $a != $b ]; then
# 	echo "a 不等于 b"
# fi


# echo "关系运算符:"

# if [ $a -eq $b ]; then
# 	echo "$a -eq $b: a 等于 b"
# else
# 	echo "$a -eq $b: a 不等于 b"
# fi

# if [ $a -ne $b ]; then
# 	echo "$a -ne $b: a 不等于 b"
# else
# 	echo "$a -ne $b: a 等于 b"
# fi


# if [ $a -gt $b ]; then
# 	echo "$a -gt $b: a 大于 b"
# else
# 	echo "$a -gt $b: a 不大于 b"
# fi

# if [ $a -ge $b ]; then
# 	echo "$a -ge $b: a 大于等于 b"
# else
# 	echo "$a -ge $b: a 小于 b"
# fi

# if [ $a -lt $b ]; then
# 	echo "$a -lt $b: a 小于 b"
# else
# 	echo "$a -lt $b: a 不小于 b"
# fi

# if [ $a -le $b ]; then
# 	echo "$a -le $b: a 小于等于 b"
# else
# 	echo "$a -le $b: a 大于 b"
# fi

# a="abc"
# b="efg"


# if [ $a = $b ]; then
# 	echo "$a = $b: a 等于 b"
# else
# 	echo "$a = $b: a 不等于 b"
# fi

# if [ -n $a ]; then
# 	echo "-n $a: 字符串长度不为0"
# fi

# a=""
# if [ -z $a ]; then
# 	echo "-z $a: 字符串长度为0" 
# fi

# file="${HOME}/Desktop/test.sh"
# echo "当前文件路径: ${file}"

# if [ -r $file ]; then
# 	echo "文件可读"
# else
# 	echo "文件不可读"
# fi

# if [ -w $file ]; then
# 	echo "文件可写"
# else
# 	echo "文件不可写"
# fi

# if [ -x $file ]; then
# 	echo "文件可执行"
# else
# 	echo "文件不可执行"
# fi

# if [ -e $file ]; then
# 	echo "文件存在"
# else
# 	echo "文件不存在"
# fi

# if [ -f $file ]; then
# 	echo "普通文件"
# else
# 	echo "特殊文件"
# fi

# if [ -d $file ]; then
# 	echo "目录文件"
# else
# 	echo "非目录文件"
# fi

# echo `date`

# printf "%-10s %-8s %-4s\n" 姓名 性别 体重kg  
# printf "%-10s %-8s %-4.2f\n" 郭靖 男 66.1234 
# printf "%-10s %-8s %-4.2f\n" 杨过 男 48.6543 
# printf "%-10s %-8s %-4.2f\n" 郭芙 女 47.9876 


# cd ../
# all=$(ls)
# for ef in ${all}; do
# 	echo $ef
# done

# if [ $(ps -ef | grep -c "ssh") -gt 1 ]; then echo "true"; fi

# int=1
# while (( $int <= 5 )); do
# 	#statements
# 	echo $int
# 	let "++int"
# done


# echo "按下  <CTRL-D> 退出"
# echo -n "输入电影名:"
# while read FILM; do
# 	echo "是的！$FILM 是一部好电影"
# done

# echo '输入 1 到 4 之间的数字:'
# echo '你输入的数字为:'
# read aNum
# case $aNum in
#     1)  echo '你选择了 1'
#     ;;
#     2)  echo '你选择了 2'
#     ;;
#     3)  echo '你选择了 3'
#     ;;
#     4)  echo '你选择了 4'
#     ;;
#     *)  echo '你没有输入 1 到 4 之间的数字'
#     ;;
# esac

# while : ;do
# 	echo "输入 1 到 5 之间的数字:"
# 	read aNum
# 	case $aNum in
# 		1|2|3|4|5) echo "你输入的数字为 $aNum!"
# 	;;
# 	*) echo "你输入的数字不是 1 到 5 之间的! 游戏结束"
# 		break
# 	;;
# 	esac
# done

func() {
	echo "call func"
}

func

funcReturn() {
	echo "计算两个输入的整数之和"
	echo "输入第一个数字:"
	read a
	echo "输入第一个数字:"
	read b
	echo "输入了 $a 和 $b"
	return $(( $a + $b ))
}

funcReturn
echo "计算结果: $?"

funWithParam(){
    echo "第一个参数为 $1 !"
    echo "第二个参数为 $2 !"
    echo "第十个参数为 $10 !"
    echo "第十个参数为 ${10} !"
    echo "第十一个参数为 ${11} !"
    echo "参数总数有 $# 个!"
    echo "作为一个字符串输出所有参数 $* !"
    for i in $@; do
    	echo $i
    done
}
funWithParam 1 2 3 4 5 6 7 8 9 34 73

echo "$!"

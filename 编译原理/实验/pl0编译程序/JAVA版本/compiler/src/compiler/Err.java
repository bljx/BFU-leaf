package compiler;

import java.io.BufferedWriter;

public class Err {

    public  int errCount = 0;
    public static final String[] errInfo = new String[]{
        "",
        "1.应是=而不是:=",
        "2.=后应为数",
        "3.标识符后应为=",
        "4.const,var,procedure 后应为标识符",
        "5.漏掉逗号或分号",
        "6.过程说明后的符号不正确",
        "7.应为语句",
        "8.程序体内语句后的符号不正确",
        "9.应为句号",
        "10.语句之间漏分号",
        "11.标识符未说明",
        "12.不可向常量或过程名赋值",
        "13.应为赋值运算符:=",
        "14.call后应为标识符",
        "15.不可调用常量或变量",
        "16.应为then",
        "17.应为分号或end",
        "18.应为do",
        "19.语句后的符号不正确",
        "20.应为关系运算符",
        "21.表达式内不可有过程标识符",
        "22.漏右括号",
        "23.因子后不可为此符号",
        "24.表达式不能以此符号开始",
        "25.这个数太大",
        "26.Not Defined Yet",
        "27.Not Defined Yet",
        "28.Not Defined Yet",
        "29.Not Defined Yet",
        "30.Not Defined Yet",    
        "31.数越界",
        "32.嵌套层数过大",
        "33.格式错误，应为右括号",
        "34.格式错误，应为左括号",
        "35.read()中的变量未声明"
    };

    /**
     * 打印错误信息
     * @param errcode 错号信息id
     * @param line  错误行数
     */
    public  void report(int errcode,int line) {
        try {
            System.out.println("*** line( "+line+"):" + errInfo[errcode] + "  ***");
            PL0.errWriter.write("*** line ( "+line+"):"+ errInfo[errcode] + "  ***\n");
            errCount++;
        }catch(Exception e){
            e.printStackTrace();
            System.out.println("***print error infomation meet with error***");
        }

    }
}

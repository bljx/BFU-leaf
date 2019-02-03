package compiler;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * 类P-code代码解释器(含代码生成函数)
 *
 * @author jiangnan
 *
 */
public class Interpreter {

    //运行栈上限
    private static final int stackSize = 1000;
    //pcode数组上线
    private static final int arraySize = 500;
    //虚拟机代码指针，取值范围[0,arraySize-1]
    public int arrayPtr = 0;
    //存放虚拟机代码的数组
    public Pcode[] pcodeArray;
    //显示虚拟代码与否
    public static boolean listswitch = true;

    public Interpreter() {
        pcodeArray = new Pcode[arraySize];
    }

    /**
     * 生成虚拟机代码
     *
     * @param f Pcodeuction.f
     * @param l Pcodeuction.l
     * @param a Pcodeuction.a
     */
    public void gen(int f, int l, int a) {
        if (arrayPtr >= arraySize) {                                                                          //超出堆栈的上限
            throw new Error("***ERROR:Program too long***");
        }
        pcodeArray[arrayPtr++] = new Pcode(f, l, a);

    }

    /**
     * 输出目标代码清单
     *
     * @param start 开始输出的位置
     */
    public void listcode(int start) {
        if (listswitch) {                                                                         //是否显示P-code代码
            for (int i = start; i < arrayPtr; i++) {
                try {
                    String msg = i + "  " + Pcode.pcode[pcodeArray[i].f] + "  " + pcodeArray[i].l + " " + pcodeArray[i].a;                //形如: lit l,a
                    System.out.println(msg);
                    PL0.pcodeWriter.write(i + "  " + msg + '\n');
                } catch (Exception e) {
                    e.printStackTrace();
                    System.out.println("***list pcode meet with error***");
                }

            }
        }
    }

    /**
     * 这个过程模拟了一台可以运行类PCODE指令的栈式计算机。 它拥有一个栈式数据段用于存放运行期数据, 拥有一个代码段用于存放类PCODE程序代码。
     * 同时还拥用数据段分配指针、指令指针、指令寄存器、局部段基址指针等寄存器。
     *
     * @param stdin 从键盘输入无符号整数
     * @param stdout 显示pcode运行过程
     */
    public void interpret(BufferedReader stdin, BufferedWriter stdout) {
        int[] runtimeStack = new int[stackSize];                  // 程序运行栈
        Arrays.fill(runtimeStack, 0);                                   //初始化
        System.out.println("***Start Interpret P_CODE***");

        int pc = 0, // pc:指令指针，
                bp = 0, //bp:指令基址，
                sp = 0; 												    		   //sp:栈顶指针

        do {

            Pcode index = pcodeArray[pc++];// index :存放当前指令, 读当前指令
            System.out.println(pc + "  " + Pcode.pcode[index.f] + " " + index.l + " " + index.a);
            switch (index.f) {
                case Pcode.LIT:                                                   // 将a的值取到栈顶
                    runtimeStack[sp++] = index.a;
                    break;
                case Pcode.OPR:                                                   // 数学、逻辑运算
                    switch (index.a) {
                        case 0:                                                          //OPR 0 0;RETURN 返回
                            sp = bp;
                            pc = runtimeStack[sp + 2];
                            bp = runtimeStack[sp + 1];
                            break;
                        case 1:                                                           //OPR 0 1 ;NEG取反
                            runtimeStack[sp - 1] = -runtimeStack[sp - 1];
                            break;
                        case 2:                                                           //OPR 0 2;ADD加法
                            sp--;
                            runtimeStack[sp - 1] += runtimeStack[sp];
                            break;
                        case 3:                                                             //OPR 0 3;SUB减法
                            sp--;
                            runtimeStack[sp - 1] -= runtimeStack[sp];
                            break;
                        case 4:                                                             //OPR 0 4;MUL乘法
                            sp--;
                            runtimeStack[sp - 1] =runtimeStack[sp - 1] * runtimeStack[sp];
                            break;
                        case 5:                                                             //OPR 0 5;DIV除法
                            sp--;
                            runtimeStack[sp - 1] /= runtimeStack[sp];
                            break;
                        case 6:                                                              //OPR 0 6;ODD对2取模mod 2
                            runtimeStack[sp - 1] %= 2;
                            break;
                        case 7:                                                              //OPR 0 7;MOD取模
                            sp--;
                            runtimeStack[sp - 1] %= runtimeStack[sp];
                            break;
                        case 8:                                                             //OPR 0 8;==判断相等
                            sp--;
                            runtimeStack[sp - 1] = (runtimeStack[sp] == runtimeStack[sp - 1] ? 1 : 0);
                            break;
                        case 9:                                                                //OPR 0 9;!=判断不相等
                            sp--;
                            runtimeStack[sp - 1] = (runtimeStack[sp] != runtimeStack[sp - 1] ? 1 : 0);
                            break;
                        case 10:                                                               //OPR 0 10;<判断小于
                            sp--;
                            runtimeStack[sp - 1] = (runtimeStack[sp] < runtimeStack[sp - 1] ? 1 : 0);
                            break;
                        case 11:                                                                //OPR 0 11;>=判断大于等于
                            sp--;
                            runtimeStack[sp - 1] = (runtimeStack[sp] >= runtimeStack[sp - 1] ? 1 : 0);
                            break;
                        case 12:                                                                //OPG 0 12;>判断大于
                            sp--;
                            runtimeStack[sp - 1] = (runtimeStack[sp] > runtimeStack[sp - 1] ? 1 : 0);
                            break;
                        case 13:                                                                 //OPG 0 13;<=判断小于等于
                            sp--;
                            runtimeStack[sp - 1] = (runtimeStack[sp] <= runtimeStack[sp - 1] ? 1 : 0);
                            break;
                        case 14:                                                                 //OPG 0 14;输出栈顶值
                            System.out.println("runtimeStack[sp - 1]" + runtimeStack[sp - 1] + ' ');
                            try {
                                stdout.write(" " + runtimeStack[sp - 1] + ' ');
                                stdout.flush();
                            } catch (Exception ex) {
                                System.out.println("***case 14 meet with error***");
                            }
                            sp--;
                            break;
                        case 15:                                                                 //OPG 0 15;输出换行
                            System.out.print("\n");
                            try {
                                stdout.write("\n");
                            } catch (Exception ex) {
                                System.out.println("***case 15 meet with error***");
                            }
                            break;
                        case 16:                                                                 //OPG 0 16;读入一行输入，置入栈顶
                            System.out.print("Please Input a Integer : ");
                            runtimeStack[sp] = 0;
                            try {
                                runtimeStack[sp] = Integer.parseInt(stdin.readLine().trim());       //读入一个整型数字
                                System.out.println(runtimeStack[sp]);
                                sp++;
                            } catch (Exception e) {
                                e.printStackTrace();
                                System.out.println("***read data meet with error***");
                            }
                            try {
                                stdout.write(" " + runtimeStack[sp] + '\n');
                                stdout.flush();
                            } catch (Exception ex) {
                                System.out.println("***case 16 meet with error***");
                            }
                            break;
                    }
                    break;
                case Pcode.LOD:                                          //取相对当前过程的数据基地址为a的内存的值到栈顶
                    runtimeStack[sp] = runtimeStack[base(index.l, runtimeStack, bp) + index.a];
                    sp++;
                    break;
                case Pcode.STO:                                         //栈顶的值存到相对当前的过程的数据基地址为a的内存
                    sp--;
                    runtimeStack[base(index.l, runtimeStack, bp) + index.a] = runtimeStack[sp];
                    break;
                case Pcode.CAL:                                                                 //调用子程序
                    runtimeStack[sp] = base(index.l, runtimeStack, bp);            //将静态作用域基地址入栈
                    runtimeStack[sp + 1] = bp;                                                //将动态作用域基地址
                    runtimeStack[sp + 2] = pc;                                               //将当前指针入栈
                    bp = sp;                                                                        //改变基地址指针值为新过程的基地址
                    pc = index.a;                                                                 //跳转至地址a
                    break;
                case Pcode.INT:                                                               //开辟空间大小为a
                    sp += index.a;
                    break;
                case Pcode.JMP:                                                               //直接跳转至a
                    pc = index.a;
                    break;
                case Pcode.JPC:
                    sp--;
                    if (runtimeStack[sp] == 0) //条件跳转至a(当栈顶指针为0时)
                    {
                        pc = index.a;
                    }
                    break;
            }
        } while (pc != 0);
    }

    /**
     * 通过给定的层次差来获得该层的堆栈帧基址
     *
     * @param l 目标层次与当前层次的层次差
     * @param runtimeStack 运行栈
     * @param b 当前层堆栈帧基地址
     * @return 目标层次的堆栈帧基地址
     */
    private int base(int l, int[] runtimeStack, int b) {
        while (l > 0) {                                                       //向上找l层
            b = runtimeStack[b];
            l--;
        }
        return b;
    }

    public void debugPcodeArray() throws IOException {
        System.out.println("***Auto-Generated Pcode Array***");
        String msg = null;
        for (int i = 0; pcodeArray[i] != null; i++) {
            msg = "" + i + "  " + Pcode.pcode[pcodeArray[i].f] + "  " + pcodeArray[i].l + "  " + pcodeArray[i].a;
            System.out.println(msg);
            PL0.pcodeWriter.write(msg + '\n');
        }
    }

}

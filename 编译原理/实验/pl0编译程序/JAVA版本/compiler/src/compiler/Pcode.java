package compiler;

/**
 * //虚拟机指令
 *
 * @author jiangnan
 *
 */
public class Pcode {

    public Pcode(int f, int l, int a) {
        this.f = f;
        this.l = l;
        this.a = a;
    }
    public static final int LIT = 0;
    public static final int OPR = 1;
    public static final int LOD = 2;
    public static final int STO = 3;
    public static final int CAL = 4;
    public static final int INT = 5;
    public static final int JMP = 6;
    public static final int JPC = 7;

    //各符号的名字
    public static final String[] pcode = new String[]{"LIT", "OPR", "LOD", "STO", "CAL", "INT", "JMP", "JPC"};
    //虚拟机代码指令
    public int f;
    //引用层与声明层的层次差
    public int l;
    //指令参数
    public int a;

}

package pk1;

public class Same {
    int val;
    public Same(int val){
        this.val=val;
    }
    Prclass obj=new Prclass(val);
    public int getVar(){
        return obj.var;
    }
};
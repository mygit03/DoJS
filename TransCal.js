//trans.js
debugger;

function pdAdd(arg)
{
    var dd=0;
    if(arg=="JG")
    {
        dd=1;
    }
    if(arg=="IG")
    {
        dd=2;
    }
    if(arg=="IJ")
    {
        dd=3;
    }
    return dd;
}

function trans2wCal(var1,var2)
{
//    var result=new Array(var1,var2,var1+var2);
    var result = new Array();
    result[0]=var1[0];
    result[1]=var1[1];
    result[2]=var1[0]+var1[1];
    var1[1]=var1[1] + 10;

    var2=var1.concat();     //将数组var1的值连接到var2

    for(var i=0;i<10;++i)
    {
        var2[i] += i+i*3;
    }

    return result;
}

function trans3wCal(var1,var2)
{
    return var1*var2+5;
}

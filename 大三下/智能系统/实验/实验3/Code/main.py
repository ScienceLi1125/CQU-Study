from tkinter import ttk
from tkinter import *
import psycopg2

 
class accounting:
    # 连接GaussDB数据库并返回结果
    def getResult(self,sql):
        conn=psycopg2.connect(database="db_2020_01",user="db_user2020_167",password="db_user@123",host="116.205.157.173",port=8000)
        # 创建指针对象
        cur=conn.cursor()
        # 获取结果
        cur.execute(sql)
        results=cur.fetchall()
        conn.commit()
        conn.close()
        return results

    #初始化操作
    def __init__(self,window):
        #知识库
        self.fact=self.getResult("select * from fact")
        #事实库
        self.rule=self.getResult("select * from rule")
        self.win=window
        self.win.title("产生式系统")
        width=1200
        height=600
        align_str='%dx%d'%(width,height)
        window.geometry(align_str)
        #treeview进行左表格显示
        self.tree=ttk.Treeview(height=31,column=("#0","#1"))
        self.tree.grid(row=0,column=0,columnspan=1)
        self.tree.heading("#0",text="编号",anchor=CENTER)
        self.tree.heading("#1",text="事实",anchor=CENTER)
 
        #绘制表格
        records=self.tree.get_children()
        for element in records:
            self.tree.delete(element)
        query="select * from fact"
        db_rows=self.getResult(query)
        db_rows.reverse()
        #填充表格
        for row in db_rows:
            self.tree.insert("",0,text=row[0],values=(row[1]))
        global list_real
        list_real=[]
        ttk.Button(text='添加——>',command=self.add).grid(row=0, column=3, sticky=W + E)
        self.message = Label(text='')
        self.message.grid(row=0, column=5, columnspan=5,sticky=W+E)
        self.message['text']="您的选择是：\n"
        self.message2 = Label(text=' ')
        self.message2.grid(row=0, column=20, columnspan=5,sticky=W+E)
        self.message2['text']="推理过程如下：\n"
        ttk.Button(text='结果——>',command=self.resultword).grid(row=0, column=12, sticky=W + E)
        ttk.Button(text='清空',command=self.clear).grid(row=0, column=30, sticky=W + E)
    
    def clear(self):
        self.message['text']="您的选择是：\n"
        self.message2['text']="推理过程如下：\n"
        global list_real
        list_real=[]
        global result
        result=[]
 
    #数据添加处理 
    def add(self):
        global list_real
        list_real.append(str(self.tree.item(self.tree.selection())['text']))
        print("lastadd",list_real)
        self.message['text']=self.message['text']+'\n'+str(self.tree.item(self.tree.selection())['text'])+str(self.tree.item(self.tree.selection())['values'][0])
        self.message.grid(row=0, column=4, columnspan=5,sticky=W+E)

        
    #自定义去重函数
    def judge_repeat(self, list1):
        tmp = set(list1)
        list2 = list(tmp)
        list2.sort()
        return list2
    
    def resultword(self):
        self.message2['text']="推理过程如下：\n"
        # 存储前提条件
        global list_real
        # 存储结果
        global result
        # 存储推理过程
        global process
        # 默认结果
        result=[]
        process=[]
        for i in self.rule:
            # 将规则库中的前提条件分割成列表
            Reason = i[1].split(",")
            # 将规则库中的结果分割成列表
            Result = i[2].split(",")
            # 判断规则库中的前提条件是否是选择的前提条件的子集
            if set(Reason).issubset(set(list_real)):
                list_real = list_real + Result
                result    = result + Result
                process.append(i[1]+"->"+i[2])
                list_real = self.judge_repeat(list_real)
                result = self.judge_repeat(result)

        # 更新gui对应文字
        for i in process:
            self.message2['text']=self.message2['text']+" "+str(i)+"\n"
        if(len(result)==0):
            self.message2['text']=self.message2['text']+"最终结果为：无法推理出结果"
        else:
            # 16，17，18，19号事实两两间不能同时出现
            l = ['16','17','18','19']
            jiaoji = set(l).intersection(set(list_real))
            if(len(jiaoji)>1):
                self.message2['text']=self.message2['text']+"最终结果为：结果矛盾，无法推理出结果"
            else:
                self.message2['text']=self.message2['text']+"最终结果为："+'\n'
                for i in result:
                    tmp = self.fact[int(i)-1][1]
                    self.message2['text']=self.message2['text']+" "+tmp+"\n"
        
if __name__ == '__main__':
    window = Tk()
    application = accounting(window)
    window.mainloop()
    
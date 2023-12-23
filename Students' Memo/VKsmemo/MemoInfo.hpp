#pragma once

template<class Node, class Info>
class MemoInfo
{
public:
    void SetYear(int year);
    void SetMonth(int month);
    void SetDate(int date);
    void SetHour(int hour);
    void SetMin(int min);
    int GetYear();
    int GetMonth();
    int GetDate();
    int GetHour();
    int GetMin();
    virtual void Save(Node* const node) = 0;
    virtual Node* Fetch(void) = 0;
    virtual void Delete(const int n) = 0;
    void Swap(Node* current);
    Node* Arrange(Node* pHead);
private:
    int year_;
    int month_;
    int date_;
    int hour_;
    int min_;
};

template<class Node, class Info>
void MemoInfo<Node,Info>::SetYear(int year)
{
    year_ = year;
}

template<class Node, class Info>
void MemoInfo<Node,Info>::SetMonth(int month)
{
    month_ = month;
}

template<class Node, class Info>
void MemoInfo<Node,Info>::SetDate(int date)
{
    date_ = date;
}

template<class Node,class Info>
void MemoInfo<Node,Info>::SetHour(int hour)
{
    hour_ = hour;
}

template<class Node, class Info>
void MemoInfo<Node,Info>::SetMin(int min)
{
    min_ = min;
}

template<class Node, class Info>
int MemoInfo<Node,Info>::GetYear()
{
    return year_;
}

template<class Node, class Info>
int MemoInfo<Node,Info>::GetMonth()
{
    return month_;
}

template<class Node, class Info>
int MemoInfo<Node,Info>::GetDate()
{
    return date_;
}

template<class Node, class Info>
int MemoInfo<Node,Info>::GetHour()
{
    return hour_;
}

template<class Node, class Info>
int MemoInfo<Node,Info>::GetMin()
{
    return min_;
}

template<class Node, class Info>
void MemoInfo<Node,Info>::Swap(Node* current)
{
    Info Tem = current->val;
    Info Tem2 = current->next->val;
    current->val = Tem2;
    current->next->val = Tem;
}

template<class Node, class Info>
Node* MemoInfo<Node,Info>::Arrange(Node* pHead)
{
    //创建辅助指针
    Node* current = pHead;//此时current即为头指针，指向第一个节点
    int num = 0;
    //用于计算共有多少个结点
    while (current)
    {
        current = current->next;
        num++;
    }
    //for循环是冒泡排序第一层，while循环是冒泡排序第二层
    for (int i = 0; i < num - 1; i++)//冒泡思想，查找num-1次
    {
        current = pHead;//每次都从头开始找
        //cout << "第" << i + 1 << "次进入循环" << endl;//测试时使用
        while (current->next)
        {
            //获取相邻两个节点中所存储的时间数据
            int y1 = current->val.GetYear();
            int mo1 = current->val.GetMonth();
            int d1 = current->val.GetDate();
            int h1 = current->val.GetHour();
            int mi1 = current->val.GetMin();
            int y2 = current->next->val.GetYear();
            int mo2 = current->next->val.GetMonth();
            int d2 = current->next->val.GetDate();
            int h2 = current->next->val.GetHour();
            int mi2 = current->next->val.GetMin();
            //冒泡排序，年份先出现的大于后出现的则直接交换
            //如果两条数据时间完全相同则不交换
            if (y1 > y2)
            {
                Swap(current);
            }
            else if (y1 == y2)
            {
                if (mo1 > mo2)
                {
                    Swap(current);
                }
                else if (mo1 == mo2)
                {
                    if (d1 > d2)
                    {
                        Swap(current);
                    }
                    if (d1 == d2)
                    {
                        if (h1 > h2)
                        {
                            Swap(current);
                        }
                        else if (h1 == h2)
                        {
                            if (mi1 > mi2)
                            {
                                Swap(current);
                            }
                            else
                            {
                                ;
                            }
                        }
                    }
                }
            }
            current = current->next;
        }
    }
    current = pHead;

    return pHead;
}

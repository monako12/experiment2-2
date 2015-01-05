#!/bin/bash

# �㳵�ס�
# NN�ˤ��ؽ���¹Ԥ���
# ��1. �ؽ����ͻҡʳؽ����ƥå׿���θ���ܿޡˤ䡤
# ��2. �ؽ���γؽ��ǡ������Ф���ؽ��ٹ礤��
# ��3. �ؽ����Ѥ��ʤ��ä��ƥ����ѥǡ������Ф���ɾ����
# ��Ԥ���ͽ��ˡ�

# ��Ȥ�����
# prompt> ./run_nn.bash $rand-seed

EXE=nn_num


# �ؽ����ƥå׿���θ���ܿ޺���
learning_fig() {
    datafile=`echo $STDOUT | sed s/txt/data/`
    figfile=`echo $STDOUT | sed s/txt/svg/`
    grep iteration $STDOUT | tr -s " " " " | cut -f3,6 -d" " > $datafile
    echo set xlabel \"iteration\" > .gnuplot
    echo set ylabel \"error\" >> .gnuplot
    echo set title \"Error transition per iteration on BP-NN\" >> .gnuplot
    echo set terminal svg >> .gnuplot
    echo set output \"$figfile\" >> .gnuplot
    echo plot \"$datafile\" with line >> .gnuplot
    gnuplot < .gnuplot
}

# 2. �ؽ���γؽ��ǡ������Ф���ؽ��ٹ礤
learned_fig() {
    datafile=`echo $STDOUT | sed s/txt/learned/`
    grep CHECK $STDOUT | cut -f2- -d" " > $datafile
}


if [ -e $EXE -a $# -eq 1 ] ; then
    STDOUT=result-seed$1.txt
    ./$EXE $1 | tee $STDOUT
    learning_fig
    learned_fig
else
    echo " You must run \"make\" before use this script."
    echo " This script requires Random-Seed to run, such as
    ./run_nn.bash 1000"
    exit 1
fi

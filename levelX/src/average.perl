use utf8;
use strict;
use warnings;
my @rep1;
my @rep2;
my @rep3;
my @rep4;
my @rep5;
my @rep6;
my @rep7;
my @rep8;
my @rep9;
my @rep10;
my @rep11;
my $i=0;
my $t=1;
my $c=0;
for($i=0;$i<135;$i++){
    $rep1[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep2[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep3[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep4[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep5[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep6[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep7[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep8[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep9[$i]=0;
}
for($i=0;$i<135;$i++){
    $rep10[$i]=0;
}
$i=0;
open(IN,"rep1000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep1[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep2000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep2[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep3000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep3[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep4000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep4[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep5000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep5[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep6000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep6[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep7000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep7[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep8000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep8[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep9000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep9[$i] = $Meigara;
$i = $i + 1

}
$i=0;
open(IN,"rep10000.txt");
while( my $Meigara = <IN> )
{
    chomp($Meigara);
    $rep10[$i] = $Meigara;
$i = $i + 1

}
$i=0;
my $f=0;
for($i=0;$i<134;$i++){
    if($rep1[$i]!=0){
	$f=$f+1;}
    if($rep2[$i]!=0){
        $f=$f+1;}
    if($rep3[$i]!=0){
        $f=$f+1;}
    if($rep4[$i]!=0){
        $f=$f+1;}
    if($rep5[$i]!=0){
        $f=$f+1;}
    if($rep6[$i]!=0){
        $f=$f+1;}
    if($rep8[$i]!=0){
        $f=$f+1;}
    if($rep9[$i]!=0){
        $f=$f+1;}
    if($rep10[$i]!=0){
        $f=$f+1;}
    $rep11[$i]=($rep1[$i]+$rep2[$i]+$rep3[$i]+$rep4[$i]+$rep5[$i]+$rep6[$i]+$rep7[$i]+$rep8[$i]+$rep9[$i]+$rep10[$i])/$f;
    $c=$i+1;
    $f=0;
    print"$c $rep11[$i]\n";
}
#print @hairetu . "\n";
#print $#hairetu . "\n";


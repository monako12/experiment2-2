use utf8;
use strict;
use warnings;
use Time::HiRes;
my $start_time = Time::HiRes::time;
my $alpha;
my $hidden=30;
my $g=0;
my $alpha2=0.1;
my $eta;
my $eta2=0.1;
my $fh;
my $buff;
for ($eta=1;$eta<19;$eta=$eta+1){
    $eta2=${eta}*0.1;
for ( $alpha=1; $alpha<10;$alpha=$alpha+1){
    $alpha2=${alpha}*0.1;
    system("cat parameter4.h | sed '13s/0.1/${alpha2}/g' > parameter3.h ");
    system("cat parameter3.h | sed '12s/0.1/${eta2}/g' > parameter6.h");
    system("cat parameter6.h  > parameter3.h");
    for($hidden=10;$hidden<60;$hidden=$hidden+10){
    system("cat parameter3.h | sed '6s/10/${hidden}/g' > parameter.h");
    system("make clean > hoge9.txt");
    system("make > hoge9.txt");
for (my $a=1000; $a <= 10000;$a=$a+1000){
    system("./nn_num ${a} > sample.txt");
    open($fh, '<', 'sample.txt');
    while ($buff = <$fh>) {
        chomp($buff);
	$buff=$buff-1;
        $g=$g+$buff;
	$buff=0;
    }
    close(($fh));
}

    $g=$g/10;
    print "$g,hidden=${hidden},alpha=${alpha2},eta=${eta2}\n";
    $g=0;
 }
}
}




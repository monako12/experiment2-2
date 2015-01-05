use utf8;
use warnings;

# ファイルリード
# readline $fh
# <$fh>

# 読み込みたいファイル名
my $file = "reportlast.txt"; 
my $hokan1;
my $hokan2=10000000;
my $gyou=0;
my $gyou1=0;
my @array2;
open(my $fh, "<", $file)
    or die "Cannot open $file: $!";

print "1: ファイルリードの一般的な記述\n";
# readline関数で、一行読み込む。
while(my $line = readline $fh){ 
    # chomp関数で、改行を取り除く
    chomp $line;
    @array2=split(/,/, $line);
    
    $hokan1=$array2[0];
    $gyou=$gyou+1;
    if($hokan1 < $hokan2){
	$line2=$hokan1;
	$hokan2=$hokan1;
	$gyou1=$gyou;
    }}
    # $line に対して何らかの処理。
    # 標準出力へ書き出し。
    print $line2, "\n";
print $gyou1, "\n";
    # ファイルがEOF( END OF FILE ) に到達するまで1行読みこみを繰り返す。


close $fh;

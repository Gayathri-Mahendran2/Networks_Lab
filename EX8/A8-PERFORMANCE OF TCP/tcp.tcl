set ns [new Simulator]

$ns color 0 blue
$ns color 1 red
$ns color 2 green
$ns color 3 yellow

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]


set f [open out.tr w]
$ns trace-all $f
set nf [open out.nam w]
$ns namtrace-all $nf

$ns duplex-link $n0 $n1 5Mb 2ms DropTail
$ns duplex-link $n1 $n2 0.5Mb 2ms DropTail
$ns duplex-link $n2 $n3 5Mb 2ms DropTail
$ns duplex-link $n1 $n4 1.5Mb 10ms DropTail
$ns duplex-link $n2 $n5 1.5Mb 10ms DropTail
$ns duplex-link $n1 $n6 1.5Mb 10ms DropTail
$ns duplex-link $n2 $n7 1.5Mb 10ms DropTail

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n2 $n3 orient right-up
$ns duplex-link-op $n1 $n4 orient left-up
$ns duplex-link-op $n2 $n5 orient right
$ns duplex-link-op $n1 $n6 orient left-down
$ns duplex-link-op $n2 $n7 orient right-down


#$ns duplex-link-op $n2 $n3 queuePos 0.5
# UDP Connection b/w 0-6  and 6-3
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
$udp0 set class_ 0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

set udp1 [new Agent/UDP]
$ns attach-agent $n6 $udp1
$udp1 set class_ 1
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

set null0 [new Agent/Null]
$ns attach-agent $n3 $null0

set null1 [new Agent/Null]
$ns attach-agent $n3 $null1

$ns connect $udp0 $null0
$ns connect $udp1 $null1

$ns at 1.0 "$cbr0 start"
$ns at 1.2 "$cbr1 start"

set tcp0 [new Agent/TCP]
$tcp0 set class_ 2
set sink0 [new Agent/TCPSink]
$ns attach-agent $n4 $tcp0
$ns attach-agent $n7 $sink0
$ns connect $tcp0 $sink0
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set tcp1 [new Agent/TCP]
$tcp1 set class_ 3
set sink1 [new Agent/TCPSink]
$ns attach-agent $n5 $tcp1
$ns attach-agent $n6 $sink1
$ns connect $tcp1 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1

$ns at 1.4 "$ftp0 start"
$ns at 1.7 "$ftp1 start" 
$ns at 1.55 "$ns detach-agent $n4 $tcp0  ; $ns detach-agent $n7 $sink0"
$ns at 1.85 "$ns detach-agent $n5 $tcp1 ; $ns detach-agent $n6 $sink1"

puts [$cbr0 set packetSize_]
puts [$cbr0 set interval_]

$ns at 3.0 "finish"
proc plotWindow {tcpSource outfile} {
   global ns
   set now [$ns now]
   set cwnd [$tcpSource set cwnd_]
   puts  $outfile  "$now $cwnd"
   $ns at [expr $now+0.1] "plotWindow $tcpSource  $outfile"
}

set outfile [open  "congestion.xg"  w]
$ns  at  0.0  "plotWindow $tcp1  $outfile"

proc finish {} {
	global ns f nf
	$ns flush-trace
	close $f
	close $nf

	puts "running nam..."
	exec nam out.nam &
	exit 0
}

$ns run


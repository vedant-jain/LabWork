set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}
#create nodes
set n0 [$ns node]
set n1 [$ns node]
#create link between n0 and n1 of b/w 1 Mb prop delay 10ms and DropTail Queue
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
#source agent
set cbr0 [new Agent/CBR]
$ns attach-agent $n0 $cbr0
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
#receiving null agent
set null0 [new Agent/Null]
$ns attach-agent $n1 $null0
#connect two agents
$ns connect $cbr0 $null0
$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

$ns at 5.0 "finish"
$ns run
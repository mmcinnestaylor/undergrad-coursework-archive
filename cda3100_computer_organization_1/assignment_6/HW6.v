module Dff1 (D, clk, Q, Qbar);
	input D, clk;
	output reg Q, Qbar;

	initial begin
		Q = 0;
		Qbar = 1;
	end

	always @(posedge clk) begin
		#1
		Q = D;
		#1
		Qbar = ~Q;
	end

endmodule

module HW6P1 (clk, Q);
	input clk;
	output [2:0] Q;

	wire Q2, Q2bar, Q1, Q1bar, Q0, Q0bar, D2, D1, D0;
	
	assign D0 = (~Q2 & Q1) | (Q2 & ~Q0);
	Dff1 C0 (D0, clk, Q0, Q0bar);

	assign D1 = Q2;	
	Dff1 C1 (D1, clk, Q1, Q1bar);
	
	assign D2 = (~Q2 & ~Q0) | (Q2 & ~Q1);	
	Dff1 C2 (D2, clk, Q2, Q2bar);
	
	assign Q[2] = Q2;
	assign Q[1] = Q1;
	assign Q[0] = Q0;

endmodule


module HW6P2 (clk, X, O);
	input clk, X;
	output O;	

	wire D1, D0, Q1, Q0, Q1bar, Q0bar;
	
	assign D0 = (~Q1 & ~Q0 & X) | (Q1 & Q0 & X) | (Q1 & ~Q0 & ~X);
	Dff1 C0 (D0, clk, Q0, Q0bar);

	assign D1 = (Q1 & ~Q0) | (~Q1 & Q0 & X);

	Dff1 C1 (D1, clk, Q1, Q1bar);
	
	assign O = Q1 & Q0;

endmodule


module test_bench ();

wire clr, clk;
reg osc;

reg [1:0] R;
reg SeqDtctinput;
integer num;

initial begin
osc = 0;
num = 0;
SeqDtctinput = 0;
end


always begin
#10 osc = ~osc;

num = (num >= 7 ) ? 0 : (num + 1);

if ((num % 2) == 0 )begin

	R = $random % 2;

	if (R > 0)
		SeqDtctinput = 1;
	else
		SeqDtctinput = 0;
end

end


assign clr=1;
assign clk=osc;

wire [2:0] HW6P1out;
HW6P1 HW6P1instance(clk, HW6P1out);

wire HW6P2out;
HW6P2 HW6P2instance(clk, SeqDtctinput, HW6P2out);

endmodule

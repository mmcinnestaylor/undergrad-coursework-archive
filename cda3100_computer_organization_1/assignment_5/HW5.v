module HW5P1 (X2, X1, X0, O);
  input X2, X1, X0;
  output O;
  assign O = (~X2 & ~X1 & X0) |  (~X2 & X1 & ~X0) | (~X2 & X1 & X0);
endmodule


module HW5P2 (S,A,B,O);
  input S, A, B;
  output O;
  assign O = (~S & A & B) | (S & ~A & B) | (S & A & ~B) | (S & A & B);
endmodule


module counter (clr, clk, OC);
	input clr, clk;
	output reg [2:0] OC;

	initial begin
		OC = 0;
	end

	always @(posedge clk) begin
		if (clr == 0)
			OC = 0;
		else
			OC = OC + 1;
	end
endmodule


module test_bench ();

wire HW5P1X2, HW5P1X1, HW5P1X0, HW5P1O;
wire HW5P2A, HW5P2B, HW5P2S, HW5P2O;
wire clr, clk;
wire [2:0] counterO;
reg osc;


initial begin
osc = 0;
end

always begin
#10 osc = ~osc;
end


assign clr=1;
assign clk=osc;
counter C1(clr, clk, counterO);

assign HW5P1X2 = counterO[2];
assign HW5P1X1 = counterO[1];
assign HW5P1X0 = counterO[0];

assign HW5P2S = counterO[2];
assign HW5P2A = counterO[1];
assign HW5P2B = counterO[0];


HW5P1 P1(HW5P1X2, HW5P1X1, HW5P1X0, HW5P1O);
HW5P2 P2(HW5P2S, HW5P2A, HW5P2B, HW5P2O);

endmodule

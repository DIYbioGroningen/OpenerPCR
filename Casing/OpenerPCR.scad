// OpenerPCR case.
// Ver 0.2
// by alc_djin and Winand 

// Variables
W = 90;
H = 170;
Z = 90;
Tk = 3; // thickness
cr = 15; // corner radius
total_H = H+2*cr;
total_W = W+2*cr;
LCD_H = 25;
LCD_W = 70;
shr = 3;
offset = cr < 1 ? Tk+shr : 0;
fd = 90; // fan diameter
 

module screw_hole(){
	cylinder(h=4*Tk, r=shr);
}

module LCD_hole(){
	cube(size = [LCD_W,LCD_H,4*Tk]);
}

module panel(){
	minkowski(){
  		cube([W,H,Tk]);
  		// rounded corners
  		cylinder(h=Tk,r=cr);
	}
}

module front_panel(){
	difference(){	
		panel();
		// LCD window
		translate([(W-LCD_W)/2,0.1*H,-Tk]){
		    LCD_hole();	
		}
		// Screw-holes
		translate([offset,offset,-Tk]){ // top-left
		    screw_hole();	
		}
		translate([W-offset,offset,-Tk]){ // top-right
		    screw_hole();		
		}
		translate([offset,H-offset,-Tk]){ // bottom-left
		    screw_hole();	
		}
		translate([W-offset,H-offset,-Tk]){ // bottom-left
		    screw_hole();
		}
	}
}

module top_hole(){
	union(){
		// Top outer
		translate([Tk,-cr,3*Tk]){
			cube([W-2*Tk,Tk,Z-4*Tk]);
		}
		// Top inner
		translate([3*Tk,-cr,5*Tk]){
			cube([W-6*Tk,4*Tk,Z-8*Tk]);
		}
	}
}

module fan_holes(){
	// fan exaust
	difference(){
		cylinder(h=4*Tk,r=fd/2);
		for(i = [0:fd/5]){
			translate([-fd/2,-fd/2+(5*i),-Tk]){
				cube([fd,3,8*Tk]);
			}	
		}
	}
	// fan screws
	translate([-fd/2,+fd/2,0]){ // top-left
		 screw_hole();	
	}
	translate([fd/2,+fd/2,0]){ // top-right
	    screw_hole();		
	}
	translate([-fd/2,-fd/2,0]){ // bottom-left
	    screw_hole();	
	}
	translate([fd/2,-fd/2,0]){ // bottom-left
	    screw_hole();
	}
}

module air_intake(){
	rotate([0,0,90]){
		for(j=[0:2*Tk]){
			translate([0,-j,0]){
				for(i=[0:H/6]){
		    		translate([i*2*Tk,cr,Tk]){
		       			cylinder(h=cos(i*10)*(Z/3)+(Z/2.5),r=Tk/3);
					}
				}
			}
		}
	}	
}	

// Body
module body(){
	difference(){
		// Solid
		translate([0,0,Tk])	{
			minkowski() {
  				cube([W,H,Z-Tk]);
  				// rounded corners
  				cylinder(r=cr,h=Tk);
			}
		}
		// Void
		translate([Tk,Tk,0]){
			minkowski() {
  				cube([W-2*Tk,H-2*Tk,Z-2*Tk]);
  				// rounded corners
  				cylinder(r=cr-Tk,h=Tk);
			}
		}
		top_hole();
		air_intake();
		translate([W+cr+(3*Tk),0,0]){
			air_intake();
		}
		translate([W-fd/2,H/1.5,Z-2*Tk]){
		fan_holes();
		}
	}
}


////// Build
translate([0,0,-Tk]){
	front_panel();
}
body();





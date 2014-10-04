// OpenerPCR case.
// Ver 0.3.1
// by DIYbio Groningen
include <OpenrPCR_logo.scad>

//Build type:
//1: complete casing
//2: back panel only, for printing
//3: front panel only, for printing
build_type = 1; 

W =  90; //Inner width of the casing in mm
H = 170; //Inner height of the casing in mm
Z =  90; //Inner depth of the casing in mm
Tk = 3;  //Thickness of casing material in mm, e.g. perspex is 3 mm
cr = 15; //Corner radius in mm
total_H = H+2*cr; //Outer height of the casing in mm
total_W = W+2*cr; //Outer width of the casing in mm
LCD_H = 25; //Width of the LCD display in mm
LCD_W = 70; //Height of the LCD display in mm
shr = 3; //Screw hole radius in mm
offset = cr < 1 ? Tk+shr : 0; //The least distance a screw hole must be from the side
fd = 90; //Fan diameter in mm


module screw_hole(){
	cylinder(h=4*Tk, r=shr);
}

module screw_holder(){
	difference(){
		cylinder(h=4*Tk, r=cr);
			translate([0,0,-Tk]){
				cylinder(h=6*Tk, r=shr);
			}
	}	
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

module OpenerPCR_logo()
{
	difference(){
		cylinder(Tk,W/2,W/2);
		translate([0,0,-Tk]){
			cylinder(4*Tk,W/2.5,W/2.5);
		}
	}
	difference(){
		translate([-W/3,-W/10,0]){
			cube([W/1.5,W/2,Tk]);
		}
		translate([0,-W/4,-Tk]){
			cylinder(4*Tk,W/2,W/2);
		}
		translate([-W/3,W/2,-Tk]){
			cylinder(4*Tk,W/6,W/6);
		}
		translate([W/3,W/2,-Tk]){
			cylinder(4*Tk,W/6,W/6);
		}
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
		translate([W/2,H/1.4,-0.5*Tk])
			OpenerPCR_logo();
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
				// al rounded
				//sphere(cr);
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
	difference(){
		union(){
			translate([0,0,Tk]){
				screw_holder();
			}
			translate([W,0,Tk]){
				screw_holder();
			}	
			translate([W,H,Tk]){
				screw_holder();
			}
			translate([0,H,Tk]){
				screw_holder();
			}
		}
		top_hole();
	}
}



//Building
if (build_type == 1)
{
   //Complete casing
	difference(){
		translate([0,0,-Tk]){
			front_panel();
		}
		translate([W/2,H/3,0]){
			rotate([180,0,0]){
				scale([0.5,0.5,1]){
					OpenerPCR_full_logo(10);
				}
			}
		}
	}
	body();
}
else if (build_type == 2)
{
  //Body only
  body();
}
else if (build_type == 3)
{
  //Front panel only
  front_panel();
}



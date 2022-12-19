
static GIFTS: [&'static str; 12]= [
	"a patridge in a pear tree",
	"two turtle doves",
	"three French hens",
	"four calling birds",
	"five golden rings",	
	"six geese-a-laying",
	"seven swans-a-swimming",
	"eight maids a-milking",
	"nine ladies dancing", // pretty sure this is illegal
	"ten lords-a-leaping",
	"eleven pipers piping",
	"twelve drummers drumming",
];

fn main() {

	for day in 1..13{
		println!("On the {}{} day of Christmas my true love gave to me ",day, get_suffix(day));
		print_gifts(day);
	}
}

fn get_suffix(num: i32) -> &'static str{
	if num == 1{
		return "st";
	}
	else if num == 2{
		return "nd";
	}
	else if num == 3{
		return "rd";
	}else {
		return "th";
	}
}

fn print_gifts(day: i32){

	for i in (0..day).rev(){
		println!("\t{}{}{}",
			if i == 0 { "and "} else {""}, // add and if the last day	
			GIFTS[i as usize], 
			if i > 0 {","} else {""} // add comma 
		);
	}
}
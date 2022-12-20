
use std::io;
use std::cmp::Ordering;
use std::io::Write;
use rand::Rng;

fn main() {
    let number = rand::thread_rng().gen_range(1, 101);

		loop {
			print!("> ");
			io::stdout().flush().unwrap();
			
			
			let mut guess = String::new();
			
			
			io::stdin().read_line(&mut guess).expect("Failed to read line");
			
			let guess: u32 = match guess.trim().parse(){
				Ok(num) => num,
				Err(_) => {
					println!("Please enter a number");
					continue;
				}
			};

			match guess.cmp(&number){
				Ordering::Less => println!("Too small"),
				Ordering::Greater => println!("Too big"),
				Ordering::Equal => {
					println!("Correct");
					break;
				},
	
			}
		}
    
}

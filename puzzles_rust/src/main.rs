
fn count_segments(s: String) -> i32 {
    let mut split = s.split_whitespace();
    let mut segments = 0;
 
    while split.next() != None
    {
        segments += 1;
    }

    return segments;
}

fn main() {
    println!("Hello, world!");
    println!("{}", count_segments("Hello, world!".to_string()));
    println!("{}", count_segments("welcome to the jungle".to_string()));
    println!("{}", count_segments("".to_string()));
    println!("{}", count_segments("hello".to_string()));
}

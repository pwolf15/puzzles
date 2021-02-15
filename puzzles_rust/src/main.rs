
fn count_segments(s: String) -> i32 {
    let mut split = s.split_whitespace();
    let mut segments = 0;
 
    while split.next() != None
    {
        segments += 1;
    }

    return segments;
}

fn num_steps(num: i32) -> i32 {

    let mut rem = num;
    let mut num_steps = 0;

    while rem != 0
    {
        num_steps += 1;
        if rem % 2 == 0
        {
            rem /= 2;
        }
        else 
        {
            rem -= 1;
        }
    }

    return num_steps;
}

#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
  pub val: i32,
  pub next: Option<Box<ListNode>>
}

impl ListNode {
  #[inline]
  fn new(val: i32) -> Self {
    ListNode {
      next: None,
      val
    }
  }
}

fn add_two_numbers(l1: Option<Box<ListNode>>, l2: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    let mut head = l1;
    while head != None
    {
        let unwrapped = head.unwrap();
        println!("{}", unwrapped.val);
        head = unwrapped.next;
    }
    return l2;
}

fn gen_list(arr: &mut[i32]) -> Option<Box<ListNode>> {

    if arr.len() == 0 {
        return None
    }

    // generate list using provided array
    let dummy = Some(Box::new(ListNode::new(0)));
    let mut head = dummy.unwrap().next;

    for i in arr {
        head = Some(Box::new(ListNode::new(*i)));
        head = head.unwrap().next;
    }

    return head;
}

fn main() {
    // println!("Hello, world!");
    // println!("{}", count_segments("Hello, world!".to_string()));
    // println!("{}", count_segments("welcome to the jungle".to_string()));
    // println!("{}", count_segments("".to_string()));
    // println!("{}", count_segments("hello".to_string()));
    // println!("{}", num_steps(14));

    let list: Option<Box<ListNode>> = Some(Box::new(ListNode::new(23)));
    let list2: Option<Box<ListNode>> = Some(Box::new(ListNode::new(23)));

    // generate list from vector array
    let list = gen_list(&mut [10, 11, 12, 13, 14]);
    // println!("{}", list.unwrap().val);

    let result = add_two_numbers(list, list2);
    // println!("{}", result.unwrap().val);

}

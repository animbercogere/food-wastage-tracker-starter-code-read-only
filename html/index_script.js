document.addEventListener("DOMContentLoaded", function() {
    $.get("/get_records", function (data) {
        console.log("On page load, get list of records from server.");
        console.log(data);
        for (let i = 0; i < data.num_records; i++) {
            let current_record = data.record_array[i];
            $("#wastage_record_table").append(addNewRow(current_record.date, current_record.meal, current_record.food_name, current_record.qty_in_oz, current_record.wastage_reason, current_record.disposal_mechanism, current_record.cost));
        } 
    });
});

var count = 0
function formClickHandler() {
  console.log("FORM CLICKED!");
  let date = document.querySelector("#date").value;
  let meal = document.querySelector("#meal").value;
  let food_name = document.querySelector("#food_name").value;
  let qty_in_oz = document.querySelector("#qty_in_oz").value;
  let wastage_reason = document.querySelector("#wastage_reason").value;
  let disposal_mechanism = document.querySelector("#disposal_mechanism").value;
  let cost = document.querySelector("#cost").value;

  $.get("/add_record", {
    date: date,
    meal: meal,
    food_name: food_name,
    qty_in_oz: qty_in_oz,
    wastage_reason: wastage_reason,
    disposal_mechanism: disposal_mechanism,
    cost: cost
  }, function (data) {
    console.log(data);
    if (data.success) {
      $("#wastage_record_table").append(addNewRow(date, meal, food_name, qty_in_oz, wastage_reason, disposal_mechanism, cost));
    }
  });
}

function addNewRow(date, meal, food_name, qty_in_oz, wastage_reason, disposal_mechanism, cost){
  var newRow = '<tr id="tbl_row_' + count + '">' +
      '<td id="date_' + count + '">' + date + '</td>' +
      '<td id="meal_' + count + '">' + meal + '</td>' +
      '<td id="food_name_' + count + '">' + food_name + '</td>' +
      '<td id="qty_in_oz_' + count + '">' + qty_in_oz + '</td>' +
      '<td id="wastage_reason_' + count + '">' + wastage_reason + '</td>' +
      '<td id="disposal_mechanism_' + count + '">' + disposal_mechanism + '</td>' +
      '<td id="cost_' + count + '">' + cost + '</td>' +
      '<td><button class="default_button" id="del_btn_' + count + '" onclick="delete_record(this.id)">X</button></td>' +
    '</tr>';
  count++;
  return newRow;
}

function backup_to_server() {
  console.log("Backup Button Clicked!");
  $.get("/backup_to_disk", function (data) {
    console.log(data);
  });
}

function delete_record(del_btn_id) {
    let row_index = del_btn_id.substring(8);

    let date = document.querySelector("#date_" + row_index).innerText;
    let meal = document.querySelector("#meal_" + row_index).innerText;
    let food_name = document.querySelector("#food_name_" + row_index).innerText;
    let qty_in_oz = document.querySelector("#qty_in_oz_" + row_index).innerText;
    let wastage_reason = document.querySelector("#wastage_reason_" + row_index).innerText;
    let disposal_mechanism = document.querySelector("#disposal_mechanism_" + row_index).innerText;
    let cost = document.querySelector("#cost_" + row_index).innerText;

    $.get("/delete_record", {
        date: date,
        meal: meal,
        food_name: food_name,
        qty_in_oz: qty_in_oz,
        wastage_reason: wastage_reason,
        disposal_mechanism: disposal_mechanism,
        cost: cost
    }, function (data) {
        console.log(data);
        if (data.success) {
            var row_container = document.getElementById("tbl_row_" + row_index);
            row_container.parentNode.removeChild(row_container);
        }
    });

    console.log("Button " + row_index + " Clicked!");
}
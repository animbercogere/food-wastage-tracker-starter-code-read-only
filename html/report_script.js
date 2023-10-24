document.addEventListener("DOMContentLoaded", function () {
    $.get("/get_wastage_report", function (data) {
        console.log("On page load, get wastage report from server.");
        console.log(data);

        populateReportCell("#food_waste_list", data.most_commonly_wasted_food_);
        populateReportCell("#most_waste_producing_meal_", data.most_waste_producing_meal_);

        

        document.querySelector("#total_cost_of_food_wasted_").innerText = "$ " + data.total_cost_of_food_wasted_;

        // document.querySelector("#most_common_wastage_reason_").innerText = data.most_common_wastage_reason_;
        populateReportCell("#most_common_wastage_reason_", data.most_common_wastage_reason_);

        // document.querySelector("#most_common_disposal_mechanism_").innerText = data.most_common_disposal_mechanism_;
        populateReportCell("#most_common_disposal_mechanism_", data.most_common_disposal_mechanism_);

        // document.querySelector("#suggested_strategies_to_reduce_waste_").innerText = data.suggested_strategies_to_reduce_waste_;
        populateReportCell("#suggested_strategies_to_reduce_waste_", data.suggested_strategies_to_reduce_waste_);

    });
});

function populateReportCell(list_id, data_array) {
    let el = document.querySelector(list_id);
    for (let i = 0; i < data_array.length; i++) {
        addListElement(el, data_array[i]);
    }
}

function addListElement(parent_element, list_string) {
    let li = document.createElement('li');
    li.innerText = list_string;
    parent_element.appendChild(li);    
}
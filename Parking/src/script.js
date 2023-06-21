document.addEventListener("DOMContentLoaded", function() {
    const carWidthInput = document.getElementById("car-width");
    const carLengthInput = document.getElementById("car-length");
    const calculateButton = document.getElementById("calculate-button");
    const bestFitContainer = document.getElementById("best-fit");
    const parkingSpot = document.getElementById("parking-spot");

    const parking = {
      floor: [
        { spot: [{ length: 20, width: 40 }, { length: 24, width: 45 }, { length: 28, width: 50 }] },
        { spot: [{ length: 40, width: 60 }, { length: 44, width: 65 }, { length: 48, width: 69 }] },
        { spot: [{ length: 60, width: 70 }, { length: 64, width: 75 }, { length: 100, width: 800 }] }
      ]
    };

    function bestSpot(parking, carLength, carWidth) {
      for (let floor = 0; floor < 3; floor++) {
        for (let spot = 0; spot < 3; spot++) {
          if (carLength <= parking.floor[floor].spot[spot].length && carWidth <= parking.floor[floor].spot[spot].width) {
            return [floor, spot];
          }
        }
      }
      return [-1, -1];
    }
  
    calculateButton.addEventListener("click", function() {
      const carWidth = parseInt(carWidthInput.value);
      const carLength = parseInt(carLengthInput.value);
  
      // Make an AJAX request to the server to calculate the best fit
      // You can use fetch() or XMLHttpRequest to send the request
  
      // Example response data (replace this with the actual response from the server)

      const result = bestSpot(parking, carLength, carWidth);

      const responseData = {
        floor: result[0],
        spot: result[1]
      };
  
      // Display the best fit result
      bestFitContainer.textContent = `Best Fit: Floor ${responseData.floor}, Spot ${responseData.spot}`;
  
      // Update the top-down view of the parking spot
      updateParkingSpot(carWidth, carLength);
    });
  
    function updateParkingSpot(carWidth, carLength) {
      // Clear the parking spot container
      parkingSpot.innerHTML = "";
  
      // Calculate the size of the parking spot based on the car dimensions
      const parkingSpotWidth = carWidth + 100;
      const parkingSpotHeight = carLength + 100;
  
      // Set the dimensions of the parking spot container
      parkingSpot.style.width = `${parkingSpotWidth}px`;
      parkingSpot.style.height = `${parkingSpotHeight}px`;
  
      // Add the car representation to the parking spot container
      const carElement = document.createElement("div");
      carElement.classList.add("car");
      carElement.style.width = `${carWidth}px`;
      carElement.style.height = `${carLength}px`;
      parkingSpot.appendChild(carElement);
    }
  });
  